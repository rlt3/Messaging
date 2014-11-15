#include <stdio.h>
#include "game.hpp"

Game::Game() 
  : _room(new Room())
  , _graphics()
{ }

Game::~Game() {
  delete _room;
}

void Game::message(const Message &msg)
{
  switch(msg.type) {
    case ATTACK: 
    case MOVEMENT:
      break;

    case DRAW: 
    case UPDATE:
    case LOCATE:
      notify(_room, msg);
      break;

    case LOCATION:
      printf("%f, %f\n", msg.data<Coordinate>().x, msg.data<Coordinate>().y);
      break;
  }
}

void Game::render()
{
  _graphics.message(Message(this, DRAW));
}

void Game::update()
{
  message(Message(this, UPDATE));
}
