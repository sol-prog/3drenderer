#include "Display.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

struct Display {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *buffer_texture;
    int width;
    int height;
    int FPS;
    uint64_t previous_frame_time;
};

Display* CreateDisplay(int width, int height, bool full_screen, bool create_streaming_texture, int FPS) {
    Display *display = malloc(sizeof(Display));
    if(!display) {
        fprintf(stderr, "Error allocating a Display struct!\n");
        return NULL;
    }

    display->window = NULL; display->renderer = NULL; display->buffer_texture = NULL;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        fprintf(stderr, "%s %s\n", "Error initalizing SDL.", SDL_GetError());
        free(display);
        return NULL;
    }

    if(full_screen) {
        SDL_DisplayMode display_mode;
        SDL_GetCurrentDisplayMode(0, &display_mode);
        // printf("Display size: width = %d, height = %d\n", display_mode.w, display_mode.h);

        display->width = display_mode.w;
        display->height = display_mode.h;
    } else {
        display->width = width;
        display->height = height;
    }

    // Create an SDL window
    display->window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, display->width, display->height, SDL_WINDOW_BORDERLESS);
    if(!display->window) {
        fprintf(stderr, "%s %s\n", "Error creating an SDL window.", SDL_GetError());
        DestroyDisplay(display);
        return NULL;
    }

    // Create an SDL renderer
    display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!display->renderer) {
        fprintf(stderr, "%s %s\n", "Error creating an SDL renderer.", SDL_GetError());
        DestroyDisplay(display);
        return NULL;
    }

    if(create_streaming_texture) {
        display->buffer_texture = SDL_CreateTexture(display->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, display->width, display->height);
        if(!display->buffer_texture) {
            fprintf(stderr, "%s %s\n", "Error creating an SDL texture.", SDL_GetError());
            DestroyDisplay(display);
            return NULL;
        }
    }

    display->FPS = FPS;
    display->previous_frame_time = SDL_GetTicks64();

    return display;
}

void GetDisplaySize(Display *display, int *width, int *height) {
    *width = display->width;
    *height = display->height;
}

void DisplayDelay(uint32_t ms) {
    SDL_Delay(ms);
}

uint64_t DisplayGetTicks(void) {
    return SDL_GetTicks64();
}

void DisplayDelayForFPS(Display *display) {
    // Fix FPS
    double frame_target_time = 1000.0 / display->FPS;
    uint32_t time_to_wait = frame_target_time - (DisplayGetTicks() - display->previous_frame_time);
    // fprintf(stderr, "%u\n", time_to_wait);
    if(time_to_wait > 0 && time_to_wait <= frame_target_time) {
        SDL_Delay(time_to_wait);
    }

    display->previous_frame_time = DisplayGetTicks();
}

void ClearDisplay(Display *display, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(display->renderer, r, g, b, a);
    SDL_RenderClear(display->renderer);
}

void DisplayRenderBuffer(Display *display, uint32_t *buffer) {
    SDL_UpdateTexture(display->buffer_texture, NULL, buffer, sizeof(uint32_t) * display->width);
    SDL_RenderCopy(display->renderer, display->buffer_texture, NULL, NULL);
}

void PresentDisplay(Display *display) {
    SDL_RenderPresent(display->renderer);
}

void DisplayProcessInput(bool *is_running) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                *is_running = false;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    *is_running = false;
                break;
        }
    }
}


void DestroyDisplay(Display *display) {
    if(display) {
        if(display->buffer_texture) SDL_DestroyTexture(display->buffer_texture);
        if(display->renderer) SDL_DestroyRenderer(display->renderer);
        if(display->window) SDL_DestroyWindow(display->window);
        SDL_Quit();
        free(display);
    }
}
