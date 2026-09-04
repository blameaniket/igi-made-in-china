

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdlib.h>

#include "window.hpp"
#include "log.hpp"




namespace Game {

Window::Window(int width, int height, const char *title)
    : m_win_width(width)
    , m_win_height(height)
    , m_win_title(title)
    , m_win_handle(nullptr) {
}

Window::~Window() {
}

void Window::init_window() {
    if (!glfwInit()) {
        log_error("failed to initialize glfw\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // for raylib floating window

    m_win_handle = glfwCreateWindow(m_win_width, m_win_height, m_win_title, NULL, NULL);
    if (!m_win_handle) {
        log_error("failed to create glfw window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_win_handle);
    glfwSwapInterval(1); // Enable V-Sync by default

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log_error("Failed to initialize GLAD OpenGL loader\n");
        exit(EXIT_FAILURE);
    }
}

bool Window::window_should_close() {
    return glfwWindowShouldClose(m_win_handle);
}


void Window::window_poll_events() {
    glfwPollEvents();
}

void Window::window_swap_buffers() {
    glfwSwapBuffers(m_win_handle);
}


}



