

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef _WIN32

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <windows.h>
#include <dwmapi.h>

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "window.hpp"
#include "log.hpp"


typedef struct WindowContext {
    GLFWwindow *window_handle;
    unsigned int window_width;
    unsigned int window_height;
} WindowContext;

static WindowContext g_win_ctx = { 0 };


static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "[GLFW ERROR %d] %s\n", error, description);
}


void init_window() {
    g_win_ctx.window_width = WINDOW_WIDTH;
    g_win_ctx.window_height = WINDOW_HEIGHT;

    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        log_error("failed to initialize glfw\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    g_win_ctx.window_handle = glfwCreateWindow(
            g_win_ctx.window_width,
            g_win_ctx.window_height,
            "stunning spoon",
            NULL,
            NULL);

    if (!g_win_ctx.window_handle) {
        log_error("failed to create glfw window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }


#ifdef _WIN32
    HWND hwnd = glfwGetWin32Window(g_win_ctx.window_handle);

    BOOL useDarkMode = TRUE;
    DwmSetWindowAttribute(
            hwnd,
            DWMWA_USE_IMMERSIVE_DARK_MODE,
            &useDarkMode,
            sizeof(useDarkMode));

    HICON hIcon = (HICON)LoadImageW(
            NULL,
            L"assets\\window_logo.ico",
            IMAGE_ICON,
            32,
            32,
            LR_LOADFROMFILE | LR_DEFAULTSIZE);

    if (hIcon) {
        SendMessageW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    } else {
        log_error("failed to load window icon\n");
    }
#endif


    int monitor_count = 0;
    GLFWmonitor **monitors = glfwGetMonitors(&monitor_count);
    if (monitor_count == 0) {
        log_error("could not find any monitor\n");
        exit(EXIT_FAILURE);
    }

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    int monitor_x, monitor_y;
    int monitor_width, monitor_height;

    glfwGetMonitorWorkarea(
            monitor,
            &monitor_x,
            &monitor_y,
            &monitor_width,
            &monitor_height);

    int x = monitor_x + (monitor_width - g_win_ctx.window_width) / 2;
    int y = monitor_y + (monitor_height - g_win_ctx.window_height) / 2;
    glfwSetWindowPos(g_win_ctx.window_handle, x, y);

    glfwMakeContextCurrent(g_win_ctx.window_handle);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log_error("Failed to initialize GLAD OpenGL loader\n");
        exit(EXIT_FAILURE);
    }
}


bool window_should_close() {
    if (g_win_ctx.window_handle == NULL) return true;
    return glfwWindowShouldClose(g_win_ctx.window_handle);
}


void close_window() {
    if (g_win_ctx.window_handle) {
        glfwDestroyWindow(g_win_ctx.window_handle);
        g_win_ctx.window_handle = NULL;
    }

    glfwTerminate();
}

void window_poll_events() {
    glfwPollEvents();
}

void window_swap_buffers() {
    glfwSwapBuffers(g_win_ctx.window_handle);
}



