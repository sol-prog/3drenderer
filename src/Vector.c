#include "Vector.h"
#include <math.h>

float vec2_length(Vec2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

float vec3_length(Vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
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
