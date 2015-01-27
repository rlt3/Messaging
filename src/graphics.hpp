#ifndef SLOW_SDL_H
#define SLOW_SDL_H

#define THIRTY_FPS    1000/30
#define SPRITE_SIZE   64
#define WINDOW_WIDTH  832
#define WINDOW_HEIGHT 704

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

enum events 
{
  KEYDOWN_EVENT = 1,
  KEYUP_EVENT,
  MOUSEMOVE_EVENT,
  MOUSECLICK_EVENT,
  MOUSEUNCLICK_EVENT
};

enum keys
{
  W_KEY = 0,  /* up    */
  A_KEY = 1,  /* left  */
  S_KEY = 2,  /* down  */
  D_KEY = 3,  /* right */
  UP_KEY = 4,
  LEFT_KEY = 5,
  DOWN_KEY = 6,
  RIGHT_KEY = 7,
  SPACE_KEY,
  ESC_KEY,
  QUIT_KEY
};

typedef SDL_Texture* Spritesheet;
typedef SDL_Rect     Frame;
typedef SDL_Rect     Rect;

void create_window();
void clear_window();
void render_window();
void destroy_texture(SDL_Texture* texture);
void destroy_window();

int  window_event();
int  key_event();
SDL_Rect event_location();

Spritesheet load_sprite(const char *filename);

void draw_sprite(Spritesheet sprite, Rect frame, Rect location);
void draw_sprite(Spritesheet sprite, Rect location);

SDL_Rect rect(int, int, int, int);

void set_draw_color(int r, int g, int b, int alpha);
void draw_rect(int x, int y, int w, int h);

void go();

#endif
