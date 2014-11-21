#ifndef SLOW_INPUT_COMPONENT_HPP
#define SLOW_INPUT_COMPONENT_HPP

#include "Component.hpp"
#include "Input.hpp"

class InputComponent : public Component, protected Input {
public:
  InputComponent(Messageable *e, Messageable *r) 
    : Component(e, r), Input(e) 
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
  void _update() 
  {
    if (_keystate[SDL_SCANCODE_W]) {
      _self->message(Message(_self, MOVE, UP));
    }

    if (_keystate[SDL_SCANCODE_A]) {
      _self->message(Message(_self, MOVE, LEFT));
    }

    if (_keystate[SDL_SCANCODE_S]) {
      _self->message(Message(_self, MOVE, DOWN));
    }

    if (_keystate[SDL_SCANCODE_D]) {
      _self->message(Message(_self, MOVE, RIGHT));
    }
  }
};

#endif

