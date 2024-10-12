#pragma once

typedef struct {
    float x;
    float y;
} Vec2;

float vec2_length(Vec2 v);
Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_mul(Vec2 a, float factor);

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

float vec3_length(Vec3 v);
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_mul(Vec3 a, float factor);

Vec3 vec3_rotate_x(Vec3 v, float alpha);
Vec3 vec3_rotate_y(Vec3 v, float alpha);
Vec3 vec3_rotate_z(Vec3 v, float alpha);
