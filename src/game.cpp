#include <stdio.h>
#include "game.hpp"

Game::Game() { 
  _room = new Room();
}

Game::~Game() {
  delete _room;
}

void
Game::message(Message msg)
{
  switch(msg.type) {
    case ATTACK: break;

    case MOVEMENT:
      notify(_room, msg);
      break;

    case LOCATE:
      notify(_room, msg);
      break;

    case LOCATION:
      printf("%f, %f\n", msg.location.x, msg.location.y);
      break;
  }
}
