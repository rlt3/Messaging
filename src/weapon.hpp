#ifndef SLOW_WEAPON_HPP
#define SLOW_WEAPON_HPP

#include "sprite.hpp"

class Weapon : public Component {
public:
  Weapon(Component* s) : Component(s)
  {
    _add(new Sprite(rect(-64, -64, 192, 192), "longsword.png", this));
  }

/*
 * TODO:
 *  Might be better to move Vector into a movement component which handles
 *  the sprite walk animation for us. This way top level messages of ANIMATE
 *  and STATE do not get conflicted with one another.
 *
 *  This way we won't have to `catch' extraneous message types to translate
 *  them to our own perhaps.
 */
  
  void message(const Message &msg)
  {
    switch(msg.type)
    {
      /* catch the animation cases and pass our own. */
      case ANIMATE: case MOVE:
        _broadcast(Message(this, STATE, msg.data<int>()));
        break;

      case ATTACK:
        _broadcast(Message(this, ANIMATE, msg.data<int>()));
        break;

      default:
        _broadcast(msg);
        break;
    }
  }
};

#endif
