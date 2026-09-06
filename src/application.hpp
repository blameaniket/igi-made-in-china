
#pragma once


#include "renderer.hpp"
#include "window.hpp"
#include "utils.hpp"
#include <cstddef>
#include <stdbool.h>


namespace Game {

struct ApplicationContext {
    size_t factor = 50;
    const unsigned int window_width = factor*16;
    const unsigned int window_height = factor*9;

    Color background_color = hex_to_rgb("#111111");
};


class Application {
public:
    Application(const ApplicationContext &spec = ApplicationContext());
    ~Application();

public:
    void run();

private:
    void loop();
    void on_update();
    bool window_should_close();

private:
    ApplicationContext m_spec;
    Window   m_window;
    Renderer m_renderer;
};

}



