

#include <iosteam>
#include "application.hpp"


namespace Game {

    Application::Application(const ApplicationContext &spec)
        : m_spec(spec)
        , m_window(spec.window_width, spec.window_height)
        , m_renderer(spec.window_width, spec.window_height) {}


    Application::~Application() {
    }



    bool Application::window_should_close() {
        return m_window.window_should_close || m_window.close;
    }

    void Application::run() {
        if (!m_window.close) {
            std::cout << "m_window.close is false" << std::endl;
        }

        m_window.init_window();
        m_renderer.renderer_init();

        while (!window_should_close()) 
        {
            loop();
        }


        m_renderer.renderer_shutdown();
        m_window.close_window();
    }

    void Application::on_update() {
        m_window.window_poll_events();
    }

    void Application::loop() {
        on_update();
        m_renderer.clear_screen(m_spec.background_color);

        m_window.window_swap_buffers();
    }

}




