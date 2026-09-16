

#include <glad/glad.h>
#include <stdlib.h>
#include <stddef.h>
#include "renderer.hpp"
#include "color.hpp"
#include "math.hpp"
#include "log.hpp"


#define MAX_BATCH_VERTICES 24000


const char *vertex_shader_source = R"(
#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_color;

out vec4 v_color;

void main()
{
    v_color = a_color;
    gl_Position = vec4(a_pos, 1.0);
}

)";


const char *fragment_shader_source = R"(
#version 330 core
in vec4 v_color;
out vec4 frag_color;

void main()
{
    frag_color = v_color;
}

)";

typedef struct Vertex {
    float x, y, z;
    float r, g, b, a;
} Vertex;

typedef enum {
    MODE_TRIANGLES = 0,
    MODE_LINES
} DrawMode;

typedef struct RenderBatch {
    GLuint shader_program;
    GLuint vao, vbo;
    GLint mvp_loc;

    Matrix projection;
    Matrix view;
    Matrix model;
    Matrix mvp;
    bool mvp_dirty;

    size_t vertex_count;
    Vertex vertices[MAX_BATCH_VERTICES];
} RenderBatch;

static RenderBatch g_renderer_ctx = { 0 };

void clear_color(Color color) {
    Color req_color = {
        .r = color.r/255.0f,
        .g = color.g/255.0f,
        .b = color.b/255.0f,
        .alpha = color.alpha,
    };

    glClearColor(
            req_color.r, 
            req_color.g, 
            req_color.b, 
            req_color.alpha);

    glClear(GL_COLOR_BUFFER_BIT);
}


void renderer_init() {
    int success;
    char info_log[512];

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        log_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        log_error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
    }

    g_renderer_ctx.shader_program = glCreateProgram();
    glAttachShader(g_renderer_ctx.shader_program, vertex_shader);
    glAttachShader(g_renderer_ctx.shader_program, fragment_shader);
    glLinkProgram(g_renderer_ctx.shader_program);

    glGetProgramiv(g_renderer_ctx.shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(g_renderer_ctx.shader_program, 512, NULL, info_log);
        log_error("ERROR::SHADER::PROGRAM::LINKING_FAILED");
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);


    // vao and dynamic vbo
    glGenVertexArrays(1, &g_renderer_ctx.vao);
    glGenBuffers(1, &g_renderer_ctx.vbo);

    glBindVertexArray(g_renderer_ctx.vao);
    glBindBuffer(GL_ARRAY_BUFFER, g_renderer_ctx.vbo);

    // allocate memory for maximum batch size upfront
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_BATCH_VERTICES, NULL, GL_DYNAMIC_DRAW);

    // attribute 0: vec3 a_pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
    glEnableVertexAttribArray(0); 

    // attribute 1: vec4 a_color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));
    glEnableVertexAttribArray(1); 

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    g_renderer_ctx.vertex_count = 0;
}

void flush_batch() {
    if (g_renderer_ctx.vertex_count == 0) return;

    glUseProgram(g_renderer_ctx.shader_program);
    glBindVertexArray(g_renderer_ctx.vao);

    // sub upload only the vertices added in this batch
    glBindBuffer(GL_ARRAY_BUFFER, g_renderer_ctx.vbo);
    glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            g_renderer_ctx.vertex_count * sizeof(Vertex),
            g_renderer_ctx.vertices);

    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)g_renderer_ctx.vertex_count);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // reset for next batch
    g_renderer_ctx.vertex_count = 0;
}

void render_triangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color) {
    if (g_renderer_ctx.vertex_count + 3 > MAX_BATCH_VERTICES) flush_batch();

    float r = color.r / 255.0f;
    float g = color.g / 255.0f;
    float b = color.b / 255.0f;
    float a = color.alpha > 1.0f ? color.alpha / 255.0f : color.alpha;

    g_renderer_ctx.vertices[g_renderer_ctx.vertex_count++] = { v1.x, v1.y, 0.0f, r, g, b, a };
    g_renderer_ctx.vertices[g_renderer_ctx.vertex_count++] = { v2.x, v2.y, 0.0f, r, g, b, a };
    g_renderer_ctx.vertices[g_renderer_ctx.vertex_count++] = { v3.x, v3.y, 0.0f, r, g, b, a };
}


void renderer_end_frame() {
    flush_batch();
}


void renderer_shutdown() {
    glDeleteVertexArrays(1, &g_renderer_ctx.vao);
    glDeleteBuffers(1, &g_renderer_ctx.vbo);
    glDeleteProgram(g_renderer_ctx.shader_program);
}


