

#pragma once


typedef struct Color {
    float r, g, b, alpha;
} Color;

Color hex_to_rgb(const char *hex);


#define LIGHTGRAY  { 200, 200, 200, 255 }
#define GRAY       { 130, 130, 130, 255 }
#define DARKGRAY   { 80, 80, 80, 255 }
#define YELLOW     { 253, 249, 0, 255 }
#define GOLD       { 255, 203, 0, 255 }
#define ORANGE     { 255, 161, 0, 255 }
#define PINK       { 255, 109, 194, 255 }
#define RED        { 230, 41, 55, 255 }
#define MAROON     { 190, 33, 55, 255 }
#define GREEN      { 0, 228, 48, 255 }
#define LIME       { 0, 158, 47, 255 }
#define DARKGREEN  { 0, 117, 44, 255 }
#define SKYBLUE    { 102, 191, 255, 255 }
#define BLUE       { 0, 121, 241, 255 }
#define DARKBLUE   { 0, 82, 172, 255 }
#define PURPLE     { 200, 122, 255, 255 }
#define VIOLET     { 135, 60, 190, 255 }
#define WHITE      { 255, 255, 255, 255 }
#define BLACK      { 0, 0, 0, 255 }
#define BLANK      { 0, 0, 0, 0 }
#define MAGENTA    { 255, 0, 255, 255 }
#define RAYWHITE   { 245, 245, 245, 255 }



