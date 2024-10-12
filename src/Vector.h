#pragma once

typedef struct {
    float x;
    float y;
} Vec2;

float vec2_length(Vec2 v);

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

float vec3_length(Vec3 v);

Vec3 vec3_rotate_x(Vec3 v, float alpha);
Vec3 vec3_rotate_y(Vec3 v, float alpha);
Vec3 vec3_rotate_z(Vec3 v, float alpha);
