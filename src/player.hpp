#ifndef SLOW_PLAYER_HPP
#define SLOW_PLAYER_HPP

#include "vector.hpp"
#include "animation.hpp"
#include "weapon.hpp"
#include "soundbite.hpp"

class Player : public Component {
public:
  Player(Component* s) : Component(s)
  {
    _add(new Vector(3, this));
    _add(new Animation("player.png", this));
    _add(new Weapon(this));
    _add(new Soundbite(this));

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

        /* translate message from inside self to outside */
      case cATTACK:
        _self->message(Message(this, eATTACK, msg.data<Rect>()));
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

      case LEFT_KEY:
        _broadcast(Message(this, DEATH));
        break;

      case SPACE_KEY:
        _broadcast(Message(this, cATTACK));
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
