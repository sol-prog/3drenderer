#include <stdio.h>
#include "Display.h"
#include "ColorBuffer.h"
#include "Drawing.h"

void draw(ColorBuffer *color_buffer) {
    ClearColorBuffer(color_buffer, 0xFF000000);
    //draw_grid(color_buffer, 20, 0xFF0000FF);
    //test_draw_rectangles(color_buffer);
    test_draw_pixels(color_buffer);
}

void update(void) {
    DisplayDelay(500);
}

int main(void) {
    int width = 800;
    int height = 600;
    bool is_running = true;

    Display *display = CreateDisplay(800, 600, true, true);
    if(!display) {
        fprintf(stderr, "Error initalizing the display!\n");
        return 1;
    }

    GetDisplaySize(display, &width, &height);

    ColorBuffer *color_buffer = CreateColorBuffer(width, height);
    if(!color_buffer) {
        fprintf(stderr, "Error initalizing the color buffer!\n");
        is_running = false;
    }

    while(is_running) {
        DisplayProcessInput(&is_running);
        update();
        ClearDisplay(display, 255, 0, 0, 255);       
        draw(color_buffer);
        DisplayRenderBuffer(display, color_buffer->data);
        PresentDisplay(display);
    }

    DestroyColorBuffer(color_buffer);
    DestroyDisplay(display);
}
