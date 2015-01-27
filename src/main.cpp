#include "graphics.hpp"
#include "game.hpp"

int main (void)
{
  create_window();

  bool running = true;

  uint32_t current_time = SDL_GetTicks();
  uint32_t last_time    = current_time;

  Game game;

  while (running) {
    current_time = SDL_GetTicks();

    switch (window_event())
    {
      case KEYDOWN_EVENT:
        switch (key_event())
        {
          case QUIT_KEY:
            running = false;
            break;

          default:
            //game.message(Message(&game, INPUT, key_event()));
            break;
        }
        break;

      case KEYUP_EVENT:
        switch (key_event())
        {
          case W_KEY: case A_KEY: case S_KEY: case D_KEY:
            //game.message(Message(&game, STOP));
            break;
        }
        break;

      case MOUSEMOVE_EVENT:
        game.message(Message(&game, MOUSE_HOVER, event_location()));
        break;

      case MOUSECLICK_EVENT:
        game.message(Message(&game, MOUSE_CLICK, event_location()));
        break;

      case MOUSEUNCLICK_EVENT:
        game.message(Message(&game, MOUSE_UNCLICK, event_location()));
        break;

      default:
        break;
    }

    if (current_time - last_time > THIRTY_FPS) 
    {
      //game.message(Message(&game, 0, (current_time - last_time)));
      last_time = current_time;
    }

    clear_window();
    game.message(Message(&game, DRAW));
    render_window();

  }

  destroy_window();

  return 0;
}
