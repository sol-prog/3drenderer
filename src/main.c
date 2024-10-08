#include <stdio.h>
#include "Display.h"
#include "ColorBuffer.h"
#include "Drawing.h"
#include "Vector.h"
#include "Mesh.h"

Triangle triangles_to_render[N_MESH_FACES];

const float FOV_FACT = 640;
Vec3 camera_pos = {0, 0, -5};
Vec3 cube_rotation = {0, 0, 0};


void setup(void) {
}

Vec2 project(Vec3 *pt3, float fov_factor) {
    return (Vec2){fov_factor * pt3->x/pt3->z, fov_factor *pt3->y/pt3->z};
}

void update(Display *display, ColorBuffer *color_buffer) {
    // Fix the FPS
    DisplayDelayForFPS(display);

    // cube_rotation.x += 0.01;
    // cube_rotation.y += 0.01;
    // cube_rotation.z += 0.01;

    // for(int i = 0; i < N_MESH_FACES; ++i) {
    //     Face mesh_face = mesh_faces[i];
    //     Vec3 face_vertices[3];
    //     face_vertices[0] = mesh_vertices[mesh_face.a - 1];
    //     face_vertices[1] = mesh_vertices[mesh_face.b - 1];
    //     face_vertices[2] = mesh_vertices[mesh_face.c - 1];

    //     for(int j = 0; j < 3; ++j) {
    //         Vec3 transformed_vertex = face_vertices[j];
    //         transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
    //         transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
    //         transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

    //         // Translate the vertex away from the camera
    //         transformed_vertex.z -= camera_pos.z;

    //         // Projection
    //         Vec2 projected_vertex = project(&transformed_vertex, FOV_FACT);

    //         // Scale, translate projected points to middle of screen
    //         projected_vertex.x += + 0.5 * color_buffer->width;
    //         projected_vertex.y += + 0.5 * color_buffer->height;

    //         triangles_to_render[i].points[j] = projected_vertex;
    //     }
    // }
}

void draw(ColorBuffer *color_buffer) {
    ClearColorBuffer(color_buffer, 0xFF000000);
    // for(int i = 0; i < N_MESH_FACES; ++i) {
    //     for(int j = 0; j < 3; ++j) {
    //         draw_rect(
    //             color_buffer,
    //             triangles_to_render[i].points[j].x,
    //             triangles_to_render[i].points[j].y, 
    //             4,
    //             4,
    //             0xFFFFFF00
    //         );
    //     }
    // }
    test_draw_lines(color_buffer);
}

int main(void) {
    int width = 800;
    int height = 600;
    int FPS = 30;
    bool is_running = true;

    Display *display = CreateDisplay(width, height, true, true, FPS);
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
        update(display, color_buffer);
        draw(color_buffer);
        DisplayRenderBuffer(display, color_buffer->data);
        PresentDisplay(display);
    }

    DestroyColorBuffer(color_buffer);
    DestroyDisplay(display);
}
