#include <stdio.h>
#include "Display.h"
#include "ColorBuffer.h"
#include "Drawing.h"
#include "Vector.h"
#include "Face.h"
#include "Mesh.h"
#include "array.h"
#include <math.h>

// some compiler do not define M_PI (after C23 M_PI was standardized)
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

ObjMesh obj_mesh;
Triangle *triangles_to_render;
size_t no_visible_faces;

const float FOV_FACT = 640;
Vec3 camera_pos = {0, 0, 0};
Vec3 obj_mesh_rotation = {M_PI, 0, 0};


void setup(void) {
}

Vec2 project(Vec3 *pt3, float fov_factor) {
    return (Vec2){fov_factor * pt3->x/pt3->z, fov_factor *pt3->y/pt3->z};
}

void update(Display *display, ColorBuffer *color_buffer) {
    // Fix the FPS
    DisplayDelayForFPS(display);

    obj_mesh_rotation.x += 0.01;
    obj_mesh_rotation.y += 0.01;
    obj_mesh_rotation.z += 0.01;

    no_visible_faces = 0;
    for(size_t i = 0; i < obj_mesh.nr_faces; ++i) {
        Face mesh_face = obj_mesh.faces_indices[i];
        Vec3 face_vertices[3];
        face_vertices[0] = obj_mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = obj_mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = obj_mesh.vertices[mesh_face.c - 1];

        Vec3 transformed_vertices[3];
        for(int j = 0; j < 3; ++j) {
            Vec3 transformed_vertex = face_vertices[j];
            transformed_vertex = vec3_rotate_x(transformed_vertex, obj_mesh_rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, obj_mesh_rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, obj_mesh_rotation.z);

            // Translate the vertex away from the camera
            transformed_vertex.z = 5;

            // Save the transformed vertices
            transformed_vertices[j] = transformed_vertex;
        }

        // Check face culling
        Vec3 ptA = transformed_vertices[0];
        Vec3 ptB = transformed_vertices[1];
        Vec3 ptC = transformed_vertices[2];
        
        // Calculate the normal vector N
        Vec3 AB = vec3_sub(ptB, ptA);
        Vec3 AC = vec3_sub(ptC, ptA);
        Vec3 N = vec3_cross(AB, AC);
        
        // A "ray" from the normal to the camera position
        Vec3 AO = vec3_sub(camera_pos, ptA);

        // dot prod between the ray and the normal
        if(vec3_dot(AO, N) < 0) {
            // we cull the face ...
            continue;
        }

        for(int j = 0; j < 3; ++j) {
            // Projection
            Vec2 projected_vertex = project(&transformed_vertices[j], FOV_FACT);

            // Scale, translate projected points to middle of screen
            projected_vertex.x += + 0.5 * color_buffer->width;
            projected_vertex.y += + 0.5 * color_buffer->height;

            triangles_to_render[no_visible_faces].points[j] = projected_vertex;
        }

        no_visible_faces++;
    }
}

void draw(ColorBuffer *color_buffer) {
    ClearColorBuffer(color_buffer, 0xFF000000);
    for(size_t i = 0; i < no_visible_faces; ++i) {
        // Draw face
        draw_triangle(color_buffer, triangles_to_render[i], 0xFFFFFF00);

        // Draw face vertices
        for(int j = 0; j < 3; ++j) {
            draw_rect(
                color_buffer,
                triangles_to_render[i].points[j].x,
                triangles_to_render[i].points[j].y, 
                4,
                4,
                0xFF0000FF
            );
        }
    }
}

int main(void) {
    int width = 800;
    int height = 600;
    int FPS = 30;
    bool is_running = true;

    ObjMeshInit(&obj_mesh);
    load_mesh(&obj_mesh, "assets/f22.obj");

    {
        ARRAY_CREATE(Triangle, arr);
        triangles_to_render = arr;
        ARRAY_RESERVE(triangles_to_render, obj_mesh.nr_faces);
    }

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
    ObjMeshDestroy(&obj_mesh);
    ARRAY_DESTROY(triangles_to_render);
}
