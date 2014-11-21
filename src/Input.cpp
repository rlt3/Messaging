#include "Input.hpp"

Input::Input(Messageable *g) : _game(g) { }

void Input::message(const Message &msg) {
  switch (msg.type) {
    case INPUT:
      _update();
      break;

    default:
      break;
  }
}

void Input::_update() {
  while (SDL_PollEvent(&_event)) {
    switch (_event.type) {
      case SDL_KEYDOWN:
        switch(_event.key.keysym.sym) {
          case SDLK_ESCAPE: case SDL_QUIT:  
            _game->message(Message(this, QUIT));
            break;
        }
    }
  }
  _keystate = SDL_GetKeyboardState(NULL);
}
