

#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils.hpp"


#define MAX_BATCH_VERTICES 24000


typedef struct Vector2 {
    float x, y;
} Vector2;

typedef struct Vector3 {
    float x, y, z;
} Vector3;

typedef struct Vertex {
    float x, y, z;
    float r, g, b, a;
} Vertex;

namespace Game {

struct RendererContext {
    GLuint shader_program;
    GLuint vao, vbo;
    GLint mvp_loc;

    // vertices part
    Vertex vertices[MAX_BATCH_VERTICES];
    int    vertex_count;
};


class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();

public:
    void renderer_init();
    void renderer_shutdown();
    void clear_screen(const Color &color);

    void draw_triangle_3d(Vector3 v1, Vector3 v2, Vector3 v3, Color color);

private:
    GLuint compile_shader(GLenum type, const char *src);
    GLuint create_program(const char *vertex_shader, const char *fragment_shader);

    void flush_batch();
    void add_vertex(Vector3 position, Color color);

private:
    RendererContext g_renderer_ctx;
    glm::mat4 projection;

};


}

