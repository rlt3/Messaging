#ifndef SLOW_PLAYER_HPP
#define SLOW_PLAYER_HPP

#include "vector.hpp"
#include "animation.hpp"
#include "weapon.hpp"

class Player : public Component {
public:
  Player(Component* s) : Component(s)
  {
    _add(new Vector(3, this));
    _add(new Animation(this));

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
  /*
   * The WASD keys are mapped directly to the direction states: 0123
   */

  void handle_input(int key)
  {
    switch(key)
    {
      case W_KEY: case A_KEY: case S_KEY: case D_KEY:
        _broadcast(Message(this, MOVE, key));
        break;

      case SPACE_KEY:
        _broadcast(Message(this, ATTACK));
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
        break;

      default:
        break;
    }
  }
};

#endif
