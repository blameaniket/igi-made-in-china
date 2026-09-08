
#pragma once


#include "renderer.hpp"
#include "game.hpp"
#include "utils.hpp"
#include <cstddef>
#include <stdbool.h>
#include <GLFW/glfw3.h>


namespace Game {

struct ApplicationContext {
    bool should_close = false;

    size_t factor = 50;
    const unsigned int window_width = factor*16;
    const unsigned int window_height = factor*9;

    Color background_color = hex_to_rgb("#111111");
    Color triangle_color   = hex_to_rgb("#ffffff");
};


class Application {
public:
    Application(const ApplicationContext &spec = ApplicationContext());
    ~Application();

public:
    void run();

private:
    void init_window();
    void close_window();
    void window_poll_events();
    void window_swap_buffers();
    void loop();
    void on_update();
    void on_render();
    bool window_should_close();

private:
    ApplicationContext m_spec;
    Renderer m_renderer;
    Game     m_game;

private:
    GLFWwindow *m_win_handle;
};

}



