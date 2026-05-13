#pragma once

#include <cstdint>
#include <random>
#include <vector>

#include "lvgl.h"

/**
 * Canvas based Matrix-style digital rain for LVGL 9.
 *
 * MatrixRain owns only the canvas, timer and pixel buffer it creates. The input
 * panel is treated as an external container by default; set
 * Config::delete_panel_on_destroy if the MatrixRain instance should delete it.
 */
class MatrixRain {
public:
    struct Config {
        uint16_t cell_width = 16;              ///< Pixel width of one digit cell.
        uint16_t cell_height = 22;             ///< Pixel height of one digit cell.
        uint16_t max_active_columns = 18;      ///< Maximum simultaneously falling columns.
        uint16_t trail_length = 12;            ///< Number of visible cells behind the head.
        uint32_t fall_period_ms = 85;          ///< Time for a column to move down one cell.
        uint32_t timer_period_ms = 25;         ///< LVGL timer tick used to drive animation.
        uint32_t spawn_min_period_ms = 450;    ///< Minimum delay between automatic spawns.
        uint32_t spawn_max_period_ms = 1500;   ///< Maximum delay between automatic spawns.
        uint8_t special_chance_percent = 8;    ///< Automatic red-head spawn chance.
        uint8_t min_trail_opa = 35;            ///< Opacity at the oldest tail cell.
        const lv_font_t * font = LV_FONT_DEFAULT;
        bool delete_panel_on_destroy = false;  ///< Also delete the caller-provided panel.
    };

    explicit MatrixRain(lv_obj_t * panel);
    MatrixRain(lv_obj_t * panel, Config config);
    ~MatrixRain();

    MatrixRain(const MatrixRain &) = delete;
    MatrixRain & operator=(const MatrixRain &) = delete;

    /**
     * Immediately creates up to n special columns. A special column has a red
     * leading digit; the rest of its trail uses Matrix green.
     */
    uint8_t newCol(uint8_t n);

    void setFallPeriod(uint32_t period_ms);
    void setTrailLength(uint16_t length);
    void setMaxActiveColumns(uint16_t count);

private:
    struct DropColumn {
        uint16_t slot = 0;
        int16_t head_row = -1;
        uint8_t lead_digit = 0;
        bool special = false;
        uint32_t next_step_ms = 0;
        std::vector<uint8_t> digits;
    };

    static void timerThunk(lv_timer_t * timer);

    void setupPanel();
    void tick();
    void stepColumns(uint32_t now_ms);
    void scheduleNextSpawn(uint32_t now_ms);
    void tryAutoSpawn(uint32_t now_ms);
    bool spawnColumn(bool special, uint32_t now_ms);
    void retireColumn(size_t index);
    void render();

    uint8_t randomDigit();
    uint8_t randomDigitExcept(uint8_t value);
    uint16_t randomFreeSlot();
    uint8_t randomPercent();
    uint32_t randomRange(uint32_t min_value, uint32_t max_value);
    uint16_t activeLimit() const;

    lv_obj_t * panel_ = nullptr;
    lv_obj_t * canvas_ = nullptr;
    lv_timer_t * timer_ = nullptr;
    Config config_;

    lv_coord_t width_ = 0;
    lv_coord_t height_ = 0;
    uint16_t slot_count_ = 0;
    uint16_t row_count_ = 0;
    uint32_t next_spawn_ms_ = 0;

    std::vector<uint8_t> canvas_buffer_;
    std::vector<bool> occupied_slots_;
    std::vector<DropColumn> columns_;

    std::mt19937 rng_;
};
