#include "Triangle.h"
#include "Drawing.h"

void draw_triangle(ColorBuffer *col_buff, Triangle tr, uint32_t color) {
    draw_line(col_buff, tr.points[0].x, tr.points[0].y, tr.points[1].x, tr.points[1].y, color);
    draw_line(col_buff, tr.points[1].x, tr.points[1].y, tr.points[2].x, tr.points[2].y, color);
    draw_line(col_buff, tr.points[2].x, tr.points[2].y, tr.points[0].x, tr.points[0].y, color);
}
