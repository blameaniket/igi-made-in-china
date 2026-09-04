


#pragma once

#include <GLFW/glfw3.h>


namespace Game {

class Window {
public:
    Window(int width, int height, const char *title);
    ~Window();

public:
    void init_window();
    void close_window();
    bool window_should_close();
    void window_poll_events();
    void window_swap_buffers();

private:
    const unsigned int m_win_width, m_win_height;
    const char *m_win_title;
    GLFWwindow *m_win_handle;
};

}




