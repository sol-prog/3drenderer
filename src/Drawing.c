#include "Drawing.h"
#include "Utils.h"
#include <stdlib.h>
#include <math.h>

void draw_grid(ColorBuffer *col_buff, int div, uint32_t color) {
    // Draw horizontal lines
    for(int y = 0; y < col_buff->height; y += div) {
        for(int x = 0; x < col_buff->width; ++x) {
            col_buff->data[col_buff->width * y + x] = color;
        }
    }

    // Draw vertical lines
    for(int y = 0; y < col_buff->height; ++y) {
        for(int x = 0; x < col_buff->width; x += div) {
            col_buff->data[col_buff->width * y + x] = color;
        }
    }
}

void draw_pixel(ColorBuffer *col_buff, int x, int y, uint32_t color) {
    if(x >= 0 && x < col_buff->width && y >= 0 && y < col_buff->height) {
        col_buff->data[col_buff->width * y + x] = color;
    }
}

void draw_rect(ColorBuffer *col_buff, int xt, int yt, int width, int height, uint32_t fill_color) {
    for(int y = yt; y < yt + height; ++y) {
        for(int x = xt; x < xt + width; ++x) {
            if(x >= 0 && x < col_buff->width && y >= 0 && y < col_buff->height) {
                col_buff->data[col_buff->width * y + x] = fill_color;
            }
        }
    }
}

void draw_line(ColorBuffer *col_buff, int x0, int y0, int x1, int y1, uint32_t color) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int side_length = abs(dx) >= abs(dy) ? abs(dx) : abs(dy);
    float x_inc = dx / (float) side_length;
    float y_inc = dy / (float) side_length;
    float curr_x = x0;
    float curr_y = y0;

    for(int i = 0; i <= side_length; ++i) {
        draw_pixel(col_buff, roundf(curr_x), roundf(curr_y), color);
        curr_x += x_inc;
        curr_y += y_inc;
    }
}

// TESTS

void test_draw_pixels(ColorBuffer *col_buff) {
    int x, y;
    uint32_t color;
    int nr_points = rand_in_range(50, 500);

    for(int p = 0; p < nr_points; ++p) {
        x = rand_in_range(0, col_buff->width);
        y = rand_in_range(0, col_buff->height);
        color = (rand_in_range(0,255) << 24) | (rand_in_range(0,255) << 16) | (rand_in_range(0,255) << 8) | rand_in_range(0,255);
        draw_pixel(col_buff, x, y, color);
    }
}

void test_draw_rectangles(ColorBuffer *col_buff) {
    int x, y, width, height;
    uint32_t color;

    int nr_rectangles = rand_in_range(10, 50);

    for(int r = 0; r < nr_rectangles; ++r) {
        x = rand_in_range(0, col_buff->width);
        y = rand_in_range(0, col_buff->height);
        width = rand_in_range(0.1 * col_buff->width, 0.3 * col_buff->width);
        height = rand_in_range(0.1 * col_buff->height, 0.3 * col_buff->height);
        color = (rand_in_range(0,255) << 24) | (rand_in_range(0,255) << 16) | (rand_in_range(0,255) << 8) | rand_in_range(0,255);

        draw_rect(col_buff, x, y, width, height, color);
    }    
}
