


#include "game.hpp"
#include "application.hpp"
#include "utils.hpp"


namespace Game {
    Game::Game() {
    }

    Game::~Game() {
    }

    Vector3 Game::set_point(Vector3 point) {
        int win_width = Application::get_window_width();
        int win_height = Application::get_window_height();

        return {
            .x = (point.x + 1.0f) * 0.5f * win_width,
            .y = (point.y + 1.0f) * 0.5f * win_height,
            .z = point.z
        };
    }

    void Game::render() {
        Color triangle_color = hex_to_rgb("#ffffff");

        Renderer& renderer = Application::GetRenderer();

        renderer.draw_triangle_3d(
                set_point({-0.5f, -0.5f, 0.0f}),
                set_point({ 0.5f, -0.5f, 0.0f}),
                set_point({ 0.0f,  0.5f, 0.0f}),
                triangle_color
                );
    }

}



