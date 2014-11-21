#ifndef SLOW_INPUT_HPP
#define SLOW_INPUT_HPP

#include "Messageable.hpp"
#include <SDL2/SDL.h>

class Input : public Messageable {
public:
  Input(Messageable *g);

  void message(const Message &msg);

protected:
  const Uint8 *_keystate;

  void _update();

private:
  SDL_Event _event;
  Messageable *_game;
};

#endif
