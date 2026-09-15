


#include "game.hpp"
#include "window.hpp"


void game_run() {
    init_window();
    while (!window_should_close()) {
        window_poll_events();
        window_swap_buffers();
    }

    close_window();

}



