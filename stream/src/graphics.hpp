#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#define FRAME_TIME    125
#define SPRITE_SIZE   64

#include "SDL2_image/SDL_image.h"
#include "entity.hpp"
#include "data_structs.hpp"

void draw_sprite(int id, int state, int frame, Point location);
void draw_sprite(int id, Point location);

int  num_sprite_frames(int id);
Rect sprite_size(int id);

void set_draw_color(int r, int g, int b, int alpha);
void draw_rect(int x, int y, int w, int h);
void draw_rect(Rect r);

#endif
