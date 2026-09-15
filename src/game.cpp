

#include "game.hpp"
#include "window.hpp"
#include "renderer.hpp"

#include "color.hpp"


void game_run() {
    init_window();

    Color game_bg = hex_to_rgb("#282828");

    while (!window_should_close()) {
        window_poll_events();
        clear_color(game_bg);

        window_swap_buffers();
    }

    close_window();

}



