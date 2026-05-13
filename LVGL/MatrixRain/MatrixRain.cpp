#include "MatrixRain.hpp"

#include <algorithm>
#include <chrono>

namespace {
lv_color_t backgroundColor() { return lv_color_hex(0x000000); }
lv_color_t matrixGreen() { return lv_color_hex(0x00ff41); }
lv_color_t headRed() { return lv_color_hex(0xff2020); }

bool timeReached(uint32_t now_ms, uint32_t target_ms)
{
    return static_cast<int32_t>(now_ms - target_ms) >= 0;
}

uint32_t makeSeed()
{
    const auto now = std::chrono::steady_clock::now().time_since_epoch().count();
    return static_cast<uint32_t>(now ^ reinterpret_cast<uintptr_t>(&now));
}
} // namespace

MatrixRain::MatrixRain(lv_obj_t * panel)
    : MatrixRain(panel, Config{})
{
}

MatrixRain::MatrixRain(lv_obj_t * panel, Config config)
    : panel_(panel), config_(config), rng_(makeSeed())
{
    if(panel_ == nullptr) return;

    config_.cell_width = std::max<uint16_t>(1, config_.cell_width);
    config_.cell_height = std::max<uint16_t>(1, config_.cell_height);
    config_.trail_length = std::max<uint16_t>(1, config_.trail_length);
    config_.spawn_max_period_ms = std::max(config_.spawn_min_period_ms, config_.spawn_max_period_ms);

    setupPanel();
    render();
    scheduleNextSpawn(lv_tick_get());
    timer_ = lv_timer_create(MatrixRain::timerThunk, config_.timer_period_ms, this);
}

MatrixRain::~MatrixRain()
{
    if(timer_ != nullptr) {
        lv_timer_delete(timer_);
        timer_ = nullptr;
    }

    if(panel_ != nullptr) {
        lv_obj_clean(panel_);
        if(config_.delete_panel_on_destroy) {
            lv_obj_delete(panel_);
        }
    }

    canvas_ = nullptr;
    panel_ = nullptr;
}

uint8_t MatrixRain::newCol(uint8_t n)
{
    uint8_t created = 0;
    const uint32_t now = lv_tick_get();
    for(uint8_t i = 0; i < n; ++i) {
        if(spawnColumn(true, now)) ++created;
    }
    if(created > 0) render();
    return created;
}

void MatrixRain::setFallPeriod(uint32_t period_ms)
{
    config_.fall_period_ms = std::max<uint32_t>(1, period_ms);
}

void MatrixRain::setTrailLength(uint16_t length)
{
    config_.trail_length = std::max<uint16_t>(1, length);
    for(auto & column : columns_) {
        if(column.digits.size() > config_.trail_length) column.digits.resize(config_.trail_length);
    }
}

void MatrixRain::setMaxActiveColumns(uint16_t count)
{
    config_.max_active_columns = count;
}

void MatrixRain::timerThunk(lv_timer_t * timer)
{
    auto * self = static_cast<MatrixRain *>(lv_timer_get_user_data(timer));
    if(self != nullptr) self->tick();
}

void MatrixRain::setupPanel()
{
    lv_obj_update_layout(panel_);
    width_ = lv_obj_get_content_width(panel_);
    height_ = lv_obj_get_content_height(panel_);
    if(width_ <= 0) width_ = lv_obj_get_width(panel_);
    if(height_ <= 0) height_ = lv_obj_get_height(panel_);
    if(width_ <= 0 || height_ <= 0) return;

    slot_count_ = static_cast<uint16_t>(std::max<lv_coord_t>(1, width_ / config_.cell_width));
    row_count_ = static_cast<uint16_t>(std::max<lv_coord_t>(1, (height_ + config_.cell_height - 1) / config_.cell_height));
    occupied_slots_.assign(slot_count_, false);
    columns_.reserve(activeLimit());

    lv_obj_clean(panel_);
    lv_obj_set_style_bg_color(panel_, backgroundColor(), 0);
    lv_obj_set_style_bg_opa(panel_, LV_OPA_COVER, 0);
    lv_obj_clear_flag(panel_, LV_OBJ_FLAG_SCROLLABLE);

    canvas_buffer_.assign(static_cast<size_t>(width_) * static_cast<size_t>(height_) * 4U, 0);
    canvas_ = lv_canvas_create(panel_);
    lv_obj_set_size(canvas_, width_, height_);
    lv_obj_align(canvas_, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_canvas_set_buffer(canvas_, canvas_buffer_.data(), width_, height_, LV_COLOR_FORMAT_ARGB8888);
    lv_canvas_fill_bg(canvas_, backgroundColor(), LV_OPA_COVER);
}

void MatrixRain::tick()
{
    if(canvas_ == nullptr) return;

    const uint32_t now = lv_tick_get();
    const size_t before = columns_.size();
    stepColumns(now);
    tryAutoSpawn(now);

    if(before != columns_.size() || !columns_.empty()) {
        render();
    }
}

void MatrixRain::stepColumns(uint32_t now_ms)
{
    bool any_changed = false;
    for(size_t i = 0; i < columns_.size();) {
        DropColumn & column = columns_[i];
        if(timeReached(now_ms, column.next_step_ms)) {
            if(column.head_row >= 0) {
                column.digits.insert(column.digits.begin(), column.lead_digit);
                if(column.digits.size() > 1) {
                    column.digits[1] = randomDigitExcept(column.lead_digit);
                }
                if(column.digits.size() > config_.trail_length) column.digits.resize(config_.trail_length);
            }

            ++column.head_row;
            column.next_step_ms = now_ms + config_.fall_period_ms;
            any_changed = true;
        }

        const int16_t oldest_row = static_cast<int16_t>(column.head_row - static_cast<int16_t>(column.digits.size()) + 1);
        if(oldest_row >= static_cast<int16_t>(row_count_)) {
            retireColumn(i);
            any_changed = true;
        } else {
            ++i;
        }
    }

    (void)any_changed;
}

void MatrixRain::scheduleNextSpawn(uint32_t now_ms)
{
    next_spawn_ms_ = now_ms + randomRange(config_.spawn_min_period_ms, config_.spawn_max_period_ms);
}

void MatrixRain::tryAutoSpawn(uint32_t now_ms)
{
    if(columns_.size() >= activeLimit()) return;
    if(!timeReached(now_ms, next_spawn_ms_)) return;

    const bool special = randomPercent() < config_.special_chance_percent;
    spawnColumn(special, now_ms);
    scheduleNextSpawn(now_ms);
}

bool MatrixRain::spawnColumn(bool special, uint32_t now_ms)
{
    if(canvas_ == nullptr) return false;
    if(columns_.size() >= activeLimit()) return false;
    if(slot_count_ == 0) return false;

    const uint16_t slot = randomFreeSlot();
    if(slot >= slot_count_) return false;

    DropColumn column;
    column.slot = slot;
    column.head_row = -1;
    column.lead_digit = randomDigit();
    column.special = special;
    column.next_step_ms = now_ms + randomRange(0, config_.fall_period_ms);
    column.digits.push_back(column.lead_digit);

    occupied_slots_[slot] = true;
    columns_.push_back(std::move(column));
    return true;
}

void MatrixRain::retireColumn(size_t index)
{
    if(index >= columns_.size()) return;
    const uint16_t slot = columns_[index].slot;
    if(slot < occupied_slots_.size()) occupied_slots_[slot] = false;
    columns_.erase(columns_.begin() + static_cast<std::ptrdiff_t>(index));
}

void MatrixRain::render()
{
    if(canvas_ == nullptr) return;

    lv_canvas_fill_bg(canvas_, backgroundColor(), LV_OPA_COVER);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas_, &layer);

    for(const auto & column : columns_) {
        const lv_coord_t x = static_cast<lv_coord_t>(column.slot * config_.cell_width);
        for(size_t offset = 0; offset < column.digits.size(); ++offset) {
            const int16_t row = static_cast<int16_t>(column.head_row - static_cast<int16_t>(offset));
            if(row < 0 || row >= static_cast<int16_t>(row_count_)) continue;

            const lv_coord_t y = static_cast<lv_coord_t>(row * config_.cell_height);
            const uint8_t digit = (offset == 0) ? column.lead_digit : column.digits[offset];
            const char text[] = {static_cast<char>('0' + digit), '\0'};

            lv_draw_label_dsc_t label_dsc;
            lv_draw_label_dsc_init(&label_dsc);
            label_dsc.text = text;
            label_dsc.font = config_.font;
            label_dsc.color = (offset == 0 && column.special) ? headRed() : matrixGreen();

            const uint16_t denominator = std::max<uint16_t>(1, config_.trail_length - 1);
            const int32_t fade = static_cast<int32_t>(LV_OPA_COVER - config_.min_trail_opa) * static_cast<int32_t>(offset) / denominator;
            label_dsc.opa = static_cast<lv_opa_t>(std::max<int32_t>(config_.min_trail_opa, LV_OPA_COVER - fade));

            lv_area_t coords = {x, y, static_cast<lv_coord_t>(x + config_.cell_width - 1), static_cast<lv_coord_t>(y + config_.cell_height - 1)};
            lv_draw_label(&layer, &label_dsc, &coords);
        }
    }

    lv_canvas_finish_layer(canvas_, &layer);
    lv_obj_invalidate(canvas_);
}

uint8_t MatrixRain::randomDigit()
{
    return static_cast<uint8_t>(randomRange(0, 9));
}

uint8_t MatrixRain::randomDigitExcept(uint8_t value)
{
    uint8_t digit = randomDigit();
    if(digit == value) digit = static_cast<uint8_t>((digit + 1U + randomRange(0, 8)) % 10U);
    return digit;
}

uint16_t MatrixRain::randomFreeSlot()
{
    std::vector<uint16_t> free_slots;
    free_slots.reserve(slot_count_);
    for(uint16_t slot = 0; slot < slot_count_; ++slot) {
        if(!occupied_slots_[slot]) free_slots.push_back(slot);
    }
    if(free_slots.empty()) return slot_count_;
    return free_slots[randomRange(0, static_cast<uint32_t>(free_slots.size() - 1))];
}

uint8_t MatrixRain::randomPercent()
{
    return static_cast<uint8_t>(randomRange(0, 99));
}

uint32_t MatrixRain::randomRange(uint32_t min_value, uint32_t max_value)
{
    if(max_value <= min_value) return min_value;
    std::uniform_int_distribution<uint32_t> distribution(min_value, max_value);
    return distribution(rng_);
}

uint16_t MatrixRain::activeLimit() const
{
    if(slot_count_ == 0) return 0;
    if(config_.max_active_columns == 0) return slot_count_;
    return std::min<uint16_t>(slot_count_, config_.max_active_columns);
}
