#include "Vector.h"
#include <math.h>

float vec2_length(Vec2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Vec2 vec2_add(Vec2 a, Vec2 b) {
    return (Vec2){.x = a.x + b.x, .y = a.y + b.y};
}

Vec2 vec2_sub(Vec2 a, Vec2 b) {
    return (Vec2){.x = a.x - b.x, .y = a.y - b.y};
}

Vec2 vec2_mul(Vec2 a, float factor) {
    return (Vec2) {.x = a.x * factor, .y = a.y * factor};
}

float vec2_dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

Vec2 vec2_normalize(Vec2 v) {
    return vec2_mul(v, vec2_length(v));
}

float vec3_length(Vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
}

Vec3 vec3_mul(Vec3 a, float factor) {
    return (Vec3) {.x = a.x * factor, .y = a.y * factor, .z = a.z * factor};
}

Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return (Vec3) {
        .x = a.y * b.z - a.z * b.y,
        .y = a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x
    };
}

float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 vec3_normalize(Vec3 v) {
    return vec3_mul(v, vec3_length(v));
}

Vec3 vec3_rotate_x(Vec3 v, float alpha){
    Vec3 vp = {
        .x = v.x,
        .y = v.y * cos(alpha) - v.z * sin(alpha),
        .z = v.y * sin(alpha) + v.z * cos(alpha)
    };
    return vp;
}

// Right hand system (OpenGL style)
// Vec3 vec3_rotate_y(Vec3 v, float alpha){
//     Vec3 vp = {
//         .x =  v.x * cos(alpha) + v.z * sin(alpha),
//         .y =  v.y,
//         .z = -v.x * sin(alpha) + v.z * cos(alpha)
//     };
//     return vp;
// }

// Left hand system (Gustavo's course convention)
Vec3 vec3_rotate_y(Vec3 v, float alpha){
    Vec3 vp = {
        .x =  v.x * cos(alpha) - v.z * sin(alpha),
        .y =  v.y,
        .z =  v.x * sin(alpha) + v.z * cos(alpha)
    };
    return vp;
}


Vec3 vec3_rotate_z(Vec3 v, float alpha){
    Vec3 vp = {
        .x = v.x * cos(alpha) - v.y * sin(alpha),
        .y = v.x * sin(alpha) + v.y * cos(alpha),
        .z = v.z
    };
    return vp;
}
