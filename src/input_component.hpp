#ifndef SLOW_INPUT_COMPONENT_HPP
#define SLOW_INPUT_COMPONENT_HPP

#include <SDL2/SDL.h>
#include "messageable.hpp"

class Input_Component : public Messageable {
public:
  Input_Component(Messageable *m) 
    : _msgable(m)
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        _update();
        break;

      default:
        break;
    }
  }

protected:
  SDL_Event    _event;
  Messageable *_msgable;

  void _update() 
  {
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_W]) {
      _msgable->message(Message(this, MOVE, UP));
    }

    if (keystate[SDL_SCANCODE_A]) {
      _msgable->message(Message(this, MOVE, LEFT));
    }

    if (keystate[SDL_SCANCODE_S]) {
      _msgable->message(Message(this, MOVE, DOWN));
    }

    if (keystate[SDL_SCANCODE_D]) {
      _msgable->message(Message(this, MOVE, RIGHT));
    }
  }
};

#endif
