#ifndef SLOW_WEAPON_HPP
#define SLOW_WEAPON_HPP

#include "component.hpp"

class Weapon : public Component {
public:
  Weapon(Component* s) : Component(s)
  {
    hitboxes[0] = { -20, -32, 128, 96 };
    hitboxes[1] = { -64,   0, 128, 64 };
    hitboxes[2] = { -20,   0, 128, 96 };
    hitboxes[3] = {   0,   0, 128, 64 };
  }
  
  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case cATTACK:
        /* do attack which creates a damage message to other entities */
        _self->message(Message(this, cATTACK, hitbox()));
        break;

      case HIT:
        msg.sender->message(Message(this, DAMAGE, 3));
        break;

      case POSITION:
        position = msg.data<Rect>();
        break;

      case MOVE:
        direction = msg.data<int>();
        break;

      default:
        _broadcast(msg);
        break;
    }
  }

protected:
  Rect position;

  Rect hitboxes[4];
  int direction;

  Rect hitbox()
  {
    Rect r;
    r.x = position.x + hitboxes[direction].x;
    r.y = position.y + hitboxes[direction].y;
    r.w = hitboxes[direction].w;
    r.h = hitboxes[direction].h;
    return r;
  }
};

#endif
