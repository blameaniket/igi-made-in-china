
#pragma once


typedef struct Vector2 {
    float x, y;
} Vector2;

typedef struct Vector3 {
    float x, y, z;
} Vector3;

typedef struct Vector4 {
    float x, y, z, w;
} Vector4;


typedef struct Color {
    float r, g, b, alpha;
} Color;


Color hex_to_rgb(const char *hex);
Vector4 color_to_vec4(const Color &color);



