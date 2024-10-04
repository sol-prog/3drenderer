#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct Display Display;

Display* CreateDisplay(int width, int height, bool full_screen, bool create_streaming_texture);
void GetDisplaySize(Display *display, int *width, int *height);
void DisplayDelay(uint32_t ms);
void ClearDisplay(Display *display, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

// Copy buffer content to display
void DisplayRenderBuffer(Display *display, uint32_t *buffer);

void PresentDisplay(Display *display);
void DestroyDisplay(Display *display);

void DisplayProcessInput(bool *is_running);
