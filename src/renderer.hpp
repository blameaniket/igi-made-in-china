


#pragma once

#include "color.hpp"
#include "math.hpp"

void renderer_init();
void renderer_shutdown();
void clear_color(Color color);
void render_triangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);
void renderer_end_frame();


