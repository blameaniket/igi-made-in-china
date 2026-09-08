

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <windows.h>
#include <dwmapi.h>

#include "resource.h"

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif
#endif


#include <chrono>
#include <iostream>

#include "application.hpp"
#include "log.hpp"


namespace Game {

    Application::Application(const ApplicationContext &spec)
        : m_spec(spec)
        , m_renderer(spec.window_width, spec.window_height)
        , m_game()
        , m_win_handle(nullptr) {}


    Application::~Application() {
    }

    void Application::init_window() {
        if (!glfwInit()) {
            log_error("failed to initialize glfw\n");
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        m_win_handle = glfwCreateWindow(m_spec.window_width, m_spec.window_height, "project igi: made in china", NULL, NULL);
        if (!m_win_handle) {
            log_error("failed to create glfw window\n");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }


#ifdef _WIN32
        HWND hwnd = glfwGetWin32Window(m_win_handle);

        RECT rect;
        GetWindowRect(hwnd, &rect);
        int window_width  = rect.right - rect.left;
        int window_height = rect.bottom - rect.top;

        int screen_width  = GetSystemMetrics(SM_CXSCREEN);
        int screen_height = GetSystemMetrics(SM_CYSCREEN);

        int x = (screen_width - window_width) / 2;
        int y = (screen_height - window_height) / 2;

        SetWindowPos(
                hwnd,
                nullptr,
                x, y,
                0, 0,
                SWP_NOZORDER | SWP_NOSIZE);


        HICON icon = LoadIcon(
                GetModuleHandle(nullptr),
                MAKEINTRESOURCE(IDI_APP_ICON));

        if (icon) {
            SendMessage(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(icon));
            SendMessage(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(icon));
        }

        BOOL use_dark_mode = TRUE;
        DwmSetWindowAttribute(
                hwnd,
                DWMWA_USE_IMMERSIVE_DARK_MODE,
                &use_dark_mode,
                sizeof(use_dark_mode));

#endif

        glfwMakeContextCurrent(m_win_handle);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            log_error("Failed to initialize GLAD OpenGL loader\n");
            exit(EXIT_FAILURE);
        }

    }

    void Application::close_window() {
        if (m_win_handle) {
            glfwDestroyWindow(m_win_handle);
            m_win_handle = NULL;
        }

        glfwTerminate();
    }

    bool Application::window_should_close() {
        bool glfw_close = glfwWindowShouldClose(m_win_handle);
        bool app_close = m_spec.should_close;

        return glfw_close || app_close;
    }


    void Application::run() {
        init_window();
        m_renderer.renderer_init();

        while (!window_should_close()) 
        {
            loop();
        }

        m_renderer.renderer_shutdown();
        close_window();
    }

    void Application::window_poll_events() {
        glfwPollEvents();
    }

    void Application::on_update() {
        glfwPollEvents();

        if (glfwGetKey(m_win_handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(m_win_handle, GLFW_TRUE);
        }
    }

    void Application::window_swap_buffers() {
        glfwSwapBuffers(m_win_handle);
    }

    void Application::loop() {
        on_update();
        m_renderer.clear_screen(m_spec.background_color);

        m_renderer.draw_triangle_3d(
                {100.0f, 100.0f, 0.0f},
                {300.0f, 100.0f, 0.0f},
                {200.0f, 300.0f, 0.0f},
                m_spec.triangle_color);

        m_renderer.flush_batch();

        window_swap_buffers();
    }

}




