

#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils.hpp"


typedef struct Vector2 {
    float x, y;
} Vector2;

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
    Renderer(int width, int height);
    ~Renderer();

public:
    void renderer_init();
    void renderer_shutdown();
    void clear_screen(const Color &color);
    void draw_rectangle(const RendererRectangle &rectangle);

private:
    GLuint compile_shader(GLenum type, const char *src);
    GLuint create_program(const char *vertex_shader, const char *fragment_shader);

private:
    RendererContext g_renderer_ctx;
    glm::mat4 projection;

};


}

