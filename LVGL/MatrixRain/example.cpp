#include "MatrixRain.hpp"

#include <memory>

static std::unique_ptr<MatrixRain> g_matrix_rain;

void create_matrix_rain_demo(lv_obj_t * parent)
{
    lv_obj_t * panel = lv_obj_create(parent);
    lv_obj_remove_style_all(panel);
    lv_obj_set_size(panel, lv_pct(100), lv_pct(100));
    lv_obj_center(panel);

    MatrixRain::Config config;
    config.cell_width = 14;
    config.cell_height = 20;
    config.trail_length = 14;
    config.max_active_columns = 20;
    config.fall_period_ms = 80;
    config.spawn_min_period_ms = 500;
    config.spawn_max_period_ms = 1600;
    config.special_chance_percent = 10;

    g_matrix_rain = std::make_unique<MatrixRain>(panel, config);

    // Create two red-head columns immediately, for example after entering a mode.
    g_matrix_rain->newCol(2);
}

void destroy_matrix_rain_demo()
{
    g_matrix_rain.reset();
}
