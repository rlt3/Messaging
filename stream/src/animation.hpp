#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "sprite.hpp"

class Animation : public Stream {
public:
  Animation(int id, Stream* up) : Stream(up, this)
  {
    _add(new Sprite(id, this));
    _add(new Sprite(LONGSWORD, this));

    character = 0;
    weapon    = 1;

    direction = 0;
  }

  /*
   * Hook into the appropriate messages and animate them.
   */
  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case MOVE:
        direction = msg.data<int>();
        _currents[character]->message(Message(this, ANIMATE, direction));
        
        /* keep weapon's state (direction) in line with the character's */
        _currents[weapon]->message(Message(this, STATE, direction));
        break;

      case BASE_ATTACK:
        _currents[character]->message(Message(this, ANIMATE, direction + COMBAT));
        _currents[weapon]->message(Message(this, ANIMATE, direction));
        break;

      case STOP:
        _currents[character]->message(Message(this, STATE, direction));
        break;

      case DEATH:
        _currents[character]->message(Message(this, ANIMATE, DIE));
        break;

      case ANIMATION_DONE:
        upstream(ANIMATION_DONE, msg.data<int>());
        break;

      case PICKUP_WEAPON:
        break;

      default:
        downstream(msg);
        break;
    }
  }

protected:
  int character;
  int weapon;

  int direction;
};

#endif
