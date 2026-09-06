
#pragma once

static constexpr const char *vertex_shader_source = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 0) in vec4 aColor;

out vec4 FragColor;
uniform mat4 u_MVP;

void main() {
    FragColor = aColor;
    gl_Position = u_MVP * vec4(aPos, 1.0);
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

