#pragma once

#include "ColorBuffer.h"

// Draw a grid every multiple of div for rows/cols
void draw_grid(ColorBuffer *col_buff, int div, uint32_t color);

void draw_pixel(ColorBuffer *col_buff, int x, int y, uint32_t color);

// Draw a filled rectangle defined by its upper left corner (x, y), width, height and fill color
void draw_rect(ColorBuffer *col_buff, int xt, int yt, int width, int height, uint32_t fill_color);

// =================  TESTS ======================

// Draw random rectangles with random colors
void test_draw_rectangles(ColorBuffer *col_buff);
// Draw random pixels with random colors
void test_draw_pixels(ColorBuffer *col_buff);
