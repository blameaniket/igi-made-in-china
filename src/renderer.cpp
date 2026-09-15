

#include <glad/glad.h>
#include "renderer.hpp"


void clear_color(Color color) {
    Color req_color = {
        .r = color.r/255.0f,
        .g = color.g/255.0f,
        .b = color.b/255.0f,
        .alpha = color.alpha,
    };

    glClearColor(
            req_color.r, 
            req_color.g, 
            req_color.b, 
            req_color.alpha);

    glClear(GL_COLOR_BUFFER_BIT);
}



void renderer_init() {
}



