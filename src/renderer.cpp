


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


    void Renderer::clear_screen(const Color &color) {
        glClearColor(color.r, color.g, color.b, color.alpha);
        glClear(GL_COLOR_BUFFER_BIT);
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
        g_renderer_ctx.vertex_count = 0;
    }

    void Renderer::renderer_shutdown() {
    }

    void Renderer::flush_batch() {
    }

    void Renderer::add_vertex(Vector3 position, Color color) {
        g_renderer_ctx.vertices[g_renderer_ctx.vertex_count++] = {
            position.x, position.y, position.z,
            color.r / 255.0f, color.g / 255.0f, 
            color.b / 255.0f, color.alpha / 255.0f
        };
    }

    void Renderer::draw_triangle_3d(Vector3 v1, Vector3 v2, Vector3 v3, Color color) {
        add_vertex(v1, color);
        add_vertex(v2, color);
        add_vertex(v3, color);
    }

}


