


#pragma once

#include <string>


namespace Genesis {

class Window {
public:
    Window(int width, int height, std::string title);
    ~Window();

    void init_window();
    void close_window();

private:
    const unsigned int m_win_width, m_win_height;
    const std::string m_win_title;
};

}






