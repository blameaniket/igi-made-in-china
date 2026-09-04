

#include "game.hpp"


namespace Game {

Game::Game(const GameConfig &game_cfg)
    : m_game_cfg(game_cfg)
    , m_window(game_cfg.window_width, game_cfg.window_height, game_cfg.window_title) {
}


void Game::run() {
    m_window.init_window();
    m_renderer.renderer_init();

    while (!m_window.window_should_close()) {
        m_window.window_poll_events();
        m_window.window_swap_buffers();
    }

    m_renderer.renderer_shutdown();
    m_window.close_window();
}


// default destructor
Game::~Game() {
}

}




