

#include "game.hpp"
#include "renderer.hpp"


namespace Game {

Game::Game(const GameContext &game_ctx)
    : m_game_ctx(game_ctx)
    , m_window(game_ctx.window_width, game_ctx.window_height)
    , m_renderer(game_ctx.window_width, game_ctx.window_height) {}


Game::~Game() {
}

void Game::run() {
    m_window.init_window();
    m_renderer.renderer_init();

    while (!m_window.window_should_close()) {
        m_window.window_poll_events();
        m_renderer.clear_screen(m_game_ctx.background_color);

        m_renderer.draw_rectangle({
            .x = 100,
            .y = 100,
            .width = 200,
            .height = 100,
            .shape_color = m_game_ctx.rectangle_color,
        });

        m_window.window_swap_buffers();
    }

    m_renderer.renderer_shutdown();
    m_window.close_window();
}


}




