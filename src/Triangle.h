#pragma once
#include "Vector.h"
#include "ColorBuffer.h"

typedef struct {
    int a;
    int b;
    int c;
} Face;

typedef struct {
    Vec2 points[3];
} Triangle;

void draw_triangle(ColorBuffer *col_buff, Triangle triangle, uint32_t color);
