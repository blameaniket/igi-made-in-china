

#include "game.hpp"
#include "window.hpp"
#include "renderer.hpp"

#include "color.hpp"


void game_run() {
    init_window();
    renderer_init();

    Color game_bg = hex_to_rgb("#282828");
    Color triangle_bg = hex_to_rgb("#ff2400");

    while (!window_should_close()) {
        clear_color(game_bg);

        render_triangle(triangle_bg);

        window_swap_buffers();
        window_poll_events();
    }

    renderer_shutdown();
    close_window();

}



