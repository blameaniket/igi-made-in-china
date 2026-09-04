


#include <glad/glad.h>
#include <cstddef>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.hpp"
#include "shader.hpp"
#include "log.hpp"
#include "utils.hpp"


namespace Game {

Renderer::Renderer(int width, int height)
    : projection(glm::ortho(
          0.0f,
          static_cast<float>(width),
          static_cast<float>(height),
          0.0f)) {}

Renderer::~Renderer() {
}

GLuint Renderer::compile_shader(GLenum type, const char *src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader, sizeof(info_log), NULL, info_log);
        log_error("SHADER ERROR: shader compilation failed:\n%s\n", info_log);
    }

    return shader;
}


GLuint Renderer::create_program(const char *vertex_shader, const char *fragment_shader) {
    GLuint vshader = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    GLuint fshader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vshader);
    glAttachShader(program, fshader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(program, sizeof(info_log), NULL, info_log);
        log_error("SHADER ERROR: shader linking failed:\n%s\n", info_log);
    }

    glDeleteShader(vshader);
    glDeleteShader(fshader);

    return program;
}

void Renderer::renderer_init() {
    g_renderer_ctx.shader = create_program(vertex_shader_source, fragment_shader_source);
    g_renderer_ctx.projection_location = glGetUniformLocation(g_renderer_ctx.shader, "projection");
    g_renderer_ctx.rectangle_location = glGetUniformLocation(g_renderer_ctx.shader, "rect");
    g_renderer_ctx.color_location = glGetUniformLocation(g_renderer_ctx.shader, "color");

    static const float unit_quad[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };


    glGenVertexArrays(1, &g_renderer_ctx.vao);
    glGenBuffers(1, &g_renderer_ctx.vbo);

    glBindVertexArray(g_renderer_ctx.vao);
    glBindBuffer(GL_ARRAY_BUFFER, g_renderer_ctx.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(unit_quad), unit_quad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::renderer_shutdown() {
    if (g_renderer_ctx.vao) {
        glDeleteVertexArrays(1, &g_renderer_ctx.vao);
        glDeleteBuffers(1, &g_renderer_ctx.vbo);
        glDeleteProgram(g_renderer_ctx.shader);
    }

    g_renderer_ctx = {};
}

void Renderer::draw_rectangle(const RendererRectangle &rectangle) {
    if (rectangle.width <= 0.0f || rectangle.height <= 0.0f) return;

    glUseProgram(g_renderer_ctx.shader);
    glUniformMatrix4fv(g_renderer_ctx.projection_location, 
            1, GL_FALSE, // single matrix and dont transpose the value
            &projection[0][0]);

    glUniform4f(g_renderer_ctx.rectangle_location, 
            rectangle.x, rectangle.y,
            rectangle.width, rectangle.height);

    glUniform4f(g_renderer_ctx.color_location,
            rectangle.shape_color.r,
            rectangle.shape_color.g,
            rectangle.shape_color.b,
            rectangle.shape_color.alpha);

    glBindVertexArray(g_renderer_ctx.vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glUseProgram(0);
}


void Renderer::clear_screen(const Color &color) {
    glClearColor(color.r, color.g, color.b, color.alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

}



