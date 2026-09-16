

#include <glad/glad.h>
#include <stdlib.h>
#include "renderer.hpp"
#include "log.hpp"


const char *vertex_shader_source = R"(
#version 330 core
layout (location = 0) in vec3 a_pos;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
}

)";


const char *fragment_shader_source = R"(
#version 330 core
out vec4 frag_color;
uniform vec4 u_color;

void main()
{
    frag_color = u_color;
}

)";


typedef struct RenderBatch {
    unsigned int shader_program;
    unsigned int vao, vbo;
    int color_loc;
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
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        log_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
    }

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
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

    static float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    glGenVertexArrays(1, &g_renderer_ctx.vao);
    glGenBuffers(1, &g_renderer_ctx.vbo);

    glBindVertexArray(g_renderer_ctx.vao);
    glBindBuffer(GL_ARRAY_BUFFER, g_renderer_ctx.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    g_renderer_ctx.color_loc = glGetUniformLocation(g_renderer_ctx.shader_program, "u_color");

}

void render_triangle(Color color) {
    glUseProgram(g_renderer_ctx.shader_program);

    glUniform4f(
            g_renderer_ctx.color_loc,
            color.r / 255.0f,
            color.g / 255.0f,
            color.b / 255.0f,
            color.alpha);

    glBindVertexArray(g_renderer_ctx.vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void renderer_shutdown() {
    glDeleteVertexArrays(1, &g_renderer_ctx.vao);
    glDeleteBuffers(1, &g_renderer_ctx.vbo);
    glDeleteProgram(g_renderer_ctx.shader_program);
}


