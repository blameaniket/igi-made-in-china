


#pragma once

#include <GLFW/glfw3.h>


namespace Game {


class Window {
public:
    Window(int width, int height);
    ~Window();

public:
    void init_window();
    void close_window();
    void window_poll_events();
    void window_swap_buffers();
    bool window_should_close();

private:
    const unsigned int m_win_width, m_win_height;
    GLFWwindow        *m_win_handle;
};

}




