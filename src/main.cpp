#include <SDL2/SDL.h>
#include "game.hpp"

#define ONE_SECOND       1000
#define THIRTY_FPS       (ONE_SECOND/30)
#define FIFTEEN_FPS      (ONE_SECOND/15)

int
main()
{
  SDL_Event event;
  Game game;

  bool running = true;

  uint32_t current_time = SDL_GetTicks();
  uint32_t last_time    = current_time;

  while (running) {

    current_time = SDL_GetTicks();

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_ESCAPE: case SDL_QUIT:  
              running = false;
              break;
          }
      }
    }

    if (current_time - last_time > THIRTY_FPS) {
      last_time = current_time;
      game.update();
    }

    game.render();
  }

  return 0;
}
