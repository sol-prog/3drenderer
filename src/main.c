#include <stdio.h>
#include "Display.h"
#include "ColorBuffer.h"
#include "Drawing.h"
#include "Vector.h"

const float FPS = 30;
const float FRAME_TARGET_TIME = 1000.0f / FPS;
uint64_t previous_frame_time = 0;

enum {N_POINTS = 9 * 9 * 9};
const float FOV_FACT = 640;
Vec3 cube_points[N_POINTS];
Vec2 proj_points[N_POINTS];
Vec3 camera_pos = {0, 0, -5};
Vec3 cube_rotation = {0, 0, 0};


void setup(void) {
    int curr_point = 0;
    for(float x = -1; x <= 1; x+= 0.25) {
        for(float y = -1; y <= 1; y+= 0.25) {
            for(float z = -1; z <= 1; z+= 0.25) {
                cube_points[curr_point] = (Vec3){x, y, z};
                curr_point++; 
            }
        }
    }
}

Vec2 project(Vec3 *pt3, float fov_factor) {
    return (Vec2){fov_factor * pt3->x/pt3->z, fov_factor *pt3->y/pt3->z};
}

void update(void) {
    // Fix FPS
    while(DisplayGetTicks() < previous_frame_time + FRAME_TARGET_TIME) {}

    previous_frame_time = DisplayGetTicks();

    cube_rotation.x += 0.01;
    cube_rotation.y += 0.01;
    cube_rotation.z += 0.01;

    for(int i = 0; i < N_POINTS; ++i) {
        Vec3 point = cube_points[i];

        // Rotation
        point = vec3_rotate_x(point, cube_rotation.x);
        point = vec3_rotate_y(point, cube_rotation.y);
        point = vec3_rotate_z(point, cube_rotation.z);

        // Camera
        point.z -= camera_pos.z;

        // Projection
        proj_points[i] = project(&point, FOV_FACT);
    }
}

void draw(ColorBuffer *color_buffer) {
    ClearColorBuffer(color_buffer, 0xFF000000);
    for(int i = 0; i < N_POINTS; ++i) {
        draw_rect(color_buffer, proj_points[i].x + 0.5 * color_buffer->width, proj_points[i].y + 0.5 * color_buffer->height, 4, 4, 0xFFFFFF00);
    }
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

    setup();

    while(is_running) {
        DisplayProcessInput(&is_running);
        update();
        draw(color_buffer);
        DisplayRenderBuffer(display, color_buffer->data);
        PresentDisplay(display);
    }

    DestroyColorBuffer(color_buffer);
    DestroyDisplay(display);
}
