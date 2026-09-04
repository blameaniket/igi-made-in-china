
#pragma once

static constexpr const char *vertex_shader_source = R"(
#version 330 core

layout(location = 0) in vec2 aPos;

uniform mat4 projection;
uniform vec4 rect;

void main()
{
    vec2 pos = rect.xy + aPos * rect.zw;
    gl_Position = projection * vec4(pos, 0.0, 1.0);
}
)";

static constexpr const char *fragment_shader_source = R"(
#version 330 core

out vec4 FragColor;

uniform vec4 color;

void main()
{
    FragColor = color;
}
)";
