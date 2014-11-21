#include "Game.hpp"

Game::Game() 
{
  _running = true;

  _current_time = SDL_GetTicks();
  _last_time    = _current_time;

  _messageables.push_back(new Graphics(this));
  _messageables.push_back(new Input(this));
  _messageables.push_back(new Room(this));
}

void Game::message(const Message &msg)
{
  switch (msg.type) {
    case QUIT:
      _running = false;
      break;

    case START:
      _loop();
      break;

    default:
      _broadcast(msg);
      break;
  }
}

void Game::_loop() {
  while (_running) {
    _current_time = SDL_GetTicks();

    _broadcast(Message(this, INPUT));

    //if (_current_time - _last_time > THIRTY_FPS) {
    //  _last_time = _current_time;
    //  _broadcast(Message(this, UPDATE));
    //}

    _broadcast(Message(this, RENDER));
  }
}
