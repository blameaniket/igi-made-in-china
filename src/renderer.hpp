
#pragma once

#include <glad/glad.h>


typedef struct Vector2 {
    float x, y;
} Vector2;

typedef struct Color {
    float r, g, b, alpha;
} Color;


namespace Game {

struct RendererContext {
    // rectangle
    GLuint shader;
    GLuint vao, vbo;
    GLint  projection_location;
    GLint  rectangle_location;
    GLint  color_location;
};

struct RendererRectangle {
    float x;
    float y;
    float width;
    float height;
    Color shape_color;
};


class Renderer {
public:
    Renderer();
    ~Renderer();

public:
    RendererContext g_renderer_ctx;

    GLuint compile_shader(GLenum type, const char *src);
    GLuint create_program(const char *vertex_shader, const char *fragment_shader);

    void renderer_init();
    void renderer_shutdown();
    void draw_rectangle(RendererRectangle rectangle);
};

}





