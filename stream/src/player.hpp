#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "movement.hpp"
#include "animation.hpp"
//#include "weapon.hpp"
//#include "soundbite.hpp"

class Player : public Stream {
public:
  Player(Stream* up) : Stream(up, this)
  {
    _add(new Movement(3, this));
    _add(new Animation(PLAYER, this));
    //_add(new Weapon(this));
    //_add(new Soundbite(this));

    downstream(POSITION, point(64, 64));
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
      //case cATTACK:
      //  _self->message(Message(this, eATTACK, msg.data<Rect>()));
      //  break;

      default:
        downstream(msg);
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
        downstream(MOVE, key);
        break;

      case LEFT_KEY:
        downstream(DEATH);
        break;

      case SPACE_KEY:
        downstream(BASE_ATTACK);
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
        downstream(STOP);
        break;

      default:
        break;
    }
  }
};

#endif
