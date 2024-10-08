#pragma once

#include "ColorBuffer.h"
#include "Triangle.h"

// Draw a grid every multiple of div for rows/cols
void draw_grid(ColorBuffer *col_buff, int div, uint32_t color);

void draw_pixel(ColorBuffer *col_buff, int x, int y, uint32_t color);

// Draw a filled rectangle defined by its upper left corner (x, y), width, height and fill color
void draw_rect(ColorBuffer *col_buff, int xt, int yt, int width, int height, uint32_t fill_color);

// Draw line - DDA algorithm
void draw_line(ColorBuffer *col_buff, int x0, int y0, int x1, int y1, uint32_t color);

// Draw a wired triangle
void draw_triangle(ColorBuffer *col_buff, Triangle triangle, uint32_t color);

// =================  TESTS ======================

// Draw random rectangles with random colors
void test_draw_rectangles(ColorBuffer *col_buff);
// Draw random pixels with random colors
void test_draw_pixels(ColorBuffer *col_buff);
// Draw some lines
void test_draw_lines(ColorBuffer *col_buff);

