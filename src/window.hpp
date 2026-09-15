

#pragma once


#define SCALE         60
#define WINDOW_WIDTH  SCALE*16
#define WINDOW_HEIGHT SCALE*10


#include <stdbool.h>

void init_window();
bool window_should_close();
void close_window();
void window_poll_events();
void window_swap_buffers();


