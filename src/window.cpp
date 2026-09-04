
#include "window.hpp"
#include <iostream>




namespace Genesis {

Window::Window(int width, int height, std::string title)
    : m_win_width(width)
    , m_win_height(height)
    , m_win_title(title) {
}

Window::~Window() {
}

void Window::init_window() {
    std::cout << m_win_width << std::endl;
    std::cout << m_win_height << std::endl;
    std::cout << m_win_title << std::endl;
}

}



