#pragma once

typedef struct {
    float x;
    float y;
} Vec2;

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

Vec3 vec3_rotate_x(Vec3 v, float alpha);
Vec3 vec3_rotate_y(Vec3 v, float alpha);
Vec3 vec3_rotate_z(Vec3 v, float alpha);
