#ifndef SLOW_PLAYER_HPP
#define SLOW_PLAYER_HPP

#include "sprite.hpp"
#include "vector.hpp"

class Player : public Component {
public:
  Player(Component* s) : Component(s)
  {
    _add(new Sprite("player.png", this));
    _add(new Vector(3, this));

    _broadcast(Message(this, POSITION, rect(64, 64, 64, 64)));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case INPUT:
        handle_input(msg.data<int>());
        break;

      case DEPUT:
        handle_deput(msg.data<int>());
        break;

      default:
        _broadcast(msg);
        break;
    }
  }

protected:
  int direction;

  /*
   * The WASD keys are mapped directly to the direction states: 0123
   */

  void handle_input(int key)
  {
    switch(key)
    {
      case W_KEY: case A_KEY: case S_KEY: case D_KEY:
        direction = key;
        _broadcast(Message(this, MOVE, direction));
        _broadcast(Message(this, ANIMATE, direction));
        break;

      case SPACE_KEY:
        _broadcast(Message(this, ANIMATE, direction + 4));
        break;

      default:
        break;
    }
  }

  void handle_deput(int key)
  {
    switch (key)
    {
      case W_KEY: case A_KEY: case S_KEY: case D_KEY:
        _broadcast(Message(this, STOP));
        _broadcast(Message(this, STATE, key));
        break;

      default:
        break;
    }
  }
};

#endif
