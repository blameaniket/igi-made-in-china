



#include <glad/glad.h>
#include <windows.h>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <dwmapi.h>

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

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

    m_win_handle = glfwCreateWindow(m_win_width, m_win_height, m_win_title, NULL, NULL);
    if (!m_win_handle) {
        log_error("failed to create glfw window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    HWND hwnd = glfwGetWin32Window(m_win_handle);

    // 3. Enable Dark Mode Title Bar via DWM API
    BOOL useDarkMode = TRUE;
    DwmSetWindowAttribute(
        hwnd,
        DWMWA_USE_IMMERSIVE_DARK_MODE,
        &useDarkMode,
        sizeof(useDarkMode));

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



