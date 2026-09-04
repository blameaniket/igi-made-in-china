
#pragma once

static const char
    *vertex_shader_source = "#version 330 core\n"
                            "layout (location = 0) in vec2 aPos;\n"
                            "uniform mat4 projection;\n"
                            "uniform vec4 rect;\n"
                            "void main()\n"
                            "{\n"
                            "    vec2 pos = rect.xy + aPos * rect.zw;\n"
                            "    gl_Position = projection * vec4(pos, 0.0, 1.0);\n"
                            "}\n";

static const char
    *fragment_shader_source = "#version 330 core\n"
                              "out vec4 FragColor;\n"
                              "uniform vec4 color;\n"
                              "void main()\n"
                              "{\n"
                              "    FragColor = color;\n"
                              "}\n";
