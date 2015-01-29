#ifndef SLOW_ANIMATION_HPP
#define SLOW_ANIMATION_HPP

#include "sprite.hpp"

class Animation : public Component {
public:
  Animation(Component* s) : Component(s)
  {
    _add(new Sprite("player.png", this));
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

      case ATTACK:
        _components[character]->message(Message(this, ANIMATE, direction + 4));
        _components[weapon]->message(Message(this, ANIMATE, direction));
        break;

      case STOP:
        _components[character]->message(Message(this, STATE, direction));
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
