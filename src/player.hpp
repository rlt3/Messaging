#ifndef SLOW_PLAYER_HPP
#define SLOW_PLAYER_HPP

#include "sprite.hpp"

class Player : public Component {
public:
  Player(Component* s) : Component(s)
  {
    _add(new Sprite("player.png", this));

    _broadcast(Message(this, POSITION, rect(64, 64, 64, 64)));
  }
};

#endif
