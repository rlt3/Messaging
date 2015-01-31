#ifndef SLOW_ANIMATION_HPP
#define SLOW_ANIMATION_HPP

#include "sprite.hpp"

/*
 * TODO:
 *   Namespace'd enum for entity states: NORTH, DEATH, COMBAT, IDLE
 *
 *   So, for our combat animation it might be
 *      component->message(Message(this, ANIMATE, direction + COMBAT));
 */

class Animation : public Component {
public:
  Animation(const char *spritefile, Component* s) : Component(s)
  {
    _add(new Sprite(spritefile, this));
    _add(new Sprite(rect(-64, -64, 192, 192), "longsword.png", this));

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
        _components[character]->message(Message(this, ANIMATE, direction));
        
        /* keep weapon's state (direction) in line with the character's */
        _components[weapon]->message(Message(this, STATE, direction));
        break;

      case cATTACK:
        _components[character]->message(Message(this, ANIMATE, direction + 4));
        _components[weapon]->message(Message(this, ANIMATE, direction));
        break;

      case STOP:
        _components[character]->message(Message(this, STATE, direction));
        break;

      case DEATH:
        _components[character]->message(Message(this, ANIMATE, 8));
        break;

        /* 
         * when calling _self, perhaps the best-case scenario is to always
         * use the _self pointer when signing it
         *
         * bug just happened where an inifite loop of ANIMATION_DONE messages
         * occurred because this keep sending the message up and then that
         * message immediately got here, which got sent back up and so on.
         */
      case ANIMATION_DONE:
        _self->message(msg);
        break;

      default:
        _broadcast(msg);
        break;
    }
  }

protected:
  int character;
  int weapon;

  int direction;
};

#endif
