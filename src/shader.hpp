
#pragma once

static constexpr const char *vertex_shader_source = R"(
#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_color;

out vec4 FragColor;
uniform mat4 u_MVP;

void main() {
    FragColor = a_color;
    gl_Position = u_MVP * vec4(a_pos, 1.0);
}


)";

static constexpr const char *fragment_shader_source = R"(
#version 330 core
in vec4 FragColor;
out vec4 FinalColor;

void main() {
    FinalColor = FragColor;
}

)";

