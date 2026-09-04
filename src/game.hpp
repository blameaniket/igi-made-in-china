
#pragma once


#include "window.hpp"
#include <string>


namespace Game {

struct GameConfig {
    const unsigned int window_width = 800;
    const unsigned int window_height = 600;
    const std::string window_title = "project igi: made in china";
};


class Game {
public:
    Game(const GameConfig &game_cfg = GameConfig());
    ~Game();

    void run();

private:
    GameConfig m_game_cfg;
    Genesis::Window m_window;
};

} // namespace Game



