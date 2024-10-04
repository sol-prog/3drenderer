#include <stdio.h>
#include <stdlib.h>

#include "ColorBuffer.h"

// gcc -std=c17 -Wall -Wextra -pedantic -g -fsanitize=address,undefined ColorBuffer.c


ColorBuffer* CreateColorBuffer(int width, int height) {
    ColorBuffer *col_buff = malloc(sizeof(ColorBuffer));
    if(!col_buff) {
        fprintf(stderr, "Can't allocate memory for the ColorBuffer!\n");
        return NULL;
    }
    col_buff->data = malloc(sizeof(uint32_t) * width * height);
    if(!col_buff->data) {
        fprintf(stderr, "Can't allocate memory for the ColorBuffer data!\n");
        free(col_buff);
        return NULL;
    }
    col_buff->width = width;
    col_buff->height = height;
    return col_buff;
}

void ClearColorBuffer(ColorBuffer *col_buff, uint32_t color) {
    for(int y = 0; y < col_buff->height; ++y) {
        for(int x = 0; x < col_buff->width; ++x) {
            col_buff->data[col_buff->width * y + x] = color;
        }
    }
}

void DestroyColorBuffer(ColorBuffer *col_buff) {
    if(col_buff) {
        if(col_buff->data) free(col_buff->data);
        free(col_buff);
    }
}

// int main(void) {
//     ColorBuffer *col_buff = CreateColorBuffer(800, 600);
//     printf("%d\t%d\n", col_buff->width, col_buff->height);
//     DestroyColorBuffer(col_buff);
// }
