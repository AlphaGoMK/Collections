# LVGL 9 MatrixRain

`MatrixRain` is a C++ LVGL 9 canvas animation that renders a Matrix-style digital rain effect.

## Files

- `MatrixRain.hpp` / `MatrixRain.cpp`: reusable class implementation.
- `example.cpp`: minimal usage example.

## Behavior

- Uses one `lv_canvas` over a caller-provided `panel` for better performance than many labels.
- Clears the panel to black and draws green falling digits.
- Each column moves down one grid cell at a time.
- When the head leaves a cell, that old cell is replaced by a random fixed digit and then fades as the trail ages.
- The leading digit keeps its original number for the life of the column.
- Special columns draw the leading digit in red; call `newCol(n)` to create up to `n` special columns immediately.
- Automatic columns use random non-overlapping slots and randomized spawn delays to avoid bursty drops.

## Basic usage

```cpp
#include "MatrixRain.hpp"

MatrixRain::Config config;
config.fall_period_ms = 80;
config.trail_length = 14;
config.max_active_columns = 20;

MatrixRain rain(panel, config);
rain.newCol(1); // one immediate red-head column
```

Destroying `MatrixRain` deletes its timer, clears the panel children and releases the canvas buffer. By default it does not delete the caller-owned `panel`; set `Config::delete_panel_on_destroy = true` only if the `MatrixRain` object owns that panel.
