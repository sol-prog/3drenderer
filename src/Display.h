#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct Display Display;

Display* CreateDisplay(int width, int height, bool full_screen, bool create_streaming_texture, int FPS);
void GetDisplaySize(Display *display, int *width, int *height);

void DisplayDelay(uint32_t ms);
// Return time in ms since Display initialization
uint64_t DisplayGetTicks(void);
// Fix the FPS
void DisplayDelayForFPS(Display *display);

void ClearDisplay(Display *display, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

// Copy buffer content to display
void DisplayRenderBuffer(Display *display, uint32_t *buffer);

void PresentDisplay(Display *display);
void DestroyDisplay(Display *display);

void DisplayProcessInput(bool *is_running);
