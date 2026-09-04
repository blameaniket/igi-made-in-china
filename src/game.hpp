
#pragma once


#include "renderer.hpp"
#include "window.hpp"
#include "utils.hpp"
#include <cstddef>


namespace Game {

struct GameContext {
    size_t factor = 60;
    const unsigned int window_width = factor*16;
    const unsigned int window_height = factor*9;

    Color background_color = hex_to_rgb("#111111");
    Color rectangle_color  = hex_to_rgb("#f69697");
};


class Game {
public:
    Game(const GameContext &game_ctx = GameContext());
    ~Game();

public:
    void run();

private:
    GameContext m_game_ctx;
    Window      m_window;
    Renderer    m_renderer;
};

} // namespace Game



