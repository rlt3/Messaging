#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "SDL2/SDL.h"
#include "entity.hpp"
#include "data_structs.hpp"

#define THIRTY_FPS    1000/30
#define WINDOW_WIDTH  832
#define WINDOW_HEIGHT 704

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

void create_window();
void clear_window();
void render_window();
void destroy_window();

int  window_event();
int  key_event();
Rect event_location();

#endif
