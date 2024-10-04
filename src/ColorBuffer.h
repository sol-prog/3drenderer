#pragma once

#include <stdint.h>

typedef struct {
    uint32_t *data;
    int width;
    int height;
} ColorBuffer;

ColorBuffer* CreateColorBuffer(int width, int height);
void ClearColorBuffer(ColorBuffer *col_buff, uint32_t color);
void DestroyColorBuffer(ColorBuffer *col_buff);
