
#pragma once


#include "renderer.hpp"
#include "window.hpp"


namespace Game {

struct GameConfig {
    const unsigned int window_width = 800;
    const unsigned int window_height = 600;
    const char        *window_title = "project igi: made in china";
};


class Game {
public:
    Game(const GameConfig &game_cfg = GameConfig());
    ~Game();

    void run();

private:
    GameConfig m_game_cfg;
    Window     m_window;
    Renderer   m_renderer;
};

} // namespace Game



