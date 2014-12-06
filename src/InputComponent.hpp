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
    //if (Input::_keystate[SDL_SCANCODE_E]) {
    //  _self->message(Message(_self, ACTION));
    //}

    /* if they aren't pressing any movement buttons */
    if (!Input::_keystate[SDL_SCANCODE_W] && 
        !Input::_keystate[SDL_SCANCODE_A] &&
        !Input::_keystate[SDL_SCANCODE_S] &&
        !Input::_keystate[SDL_SCANCODE_D]) {
      _self->message(Message(_self, STOP));
      return;
    }

    //if (Input::_keystate[SDL_SCANCODE_W] && Input::_keystate[SDL_SCANCODE_A]) {
    //  _self->message(Message(_self, MOVE, NORTHWEST));
    //  return;
    //}

    //if (Input::_keystate[SDL_SCANCODE_W] && Input::_keystate[SDL_SCANCODE_D]) {
    //  _self->message(Message(_self, MOVE, NORTHEAST));
    //  return;
    //}
    //
    //if (Input::_keystate[SDL_SCANCODE_S] && Input::_keystate[SDL_SCANCODE_A]) {
    //  _self->message(Message(_self, MOVE, SOUTHWEST));
    //  return;
    //}

    //if (Input::_keystate[SDL_SCANCODE_S] && Input::_keystate[SDL_SCANCODE_D]) {
    //  _self->message(Message(_self, MOVE, SOUTHEAST));
    //  return;
    //}

    if (Input::_keystate[SDL_SCANCODE_W]) {
      _self->message(Message(_self, MOVE, NORTH));
      return;
    }

    //if (Input::_keystate[SDL_SCANCODE_A]) {
    //  _self->message(Message(_self, MOVE, WEST));
    //  return;
    //}

    if (Input::_keystate[SDL_SCANCODE_S]) {
      _self->message(Message(_self, MOVE, SOUTH));
      return;
    }

    //if (Input::_keystate[SDL_SCANCODE_D]) {
    //  _self->message(Message(_self, MOVE, EAST));
    //  return;
    //}
  }
};

#endif

