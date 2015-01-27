#ifndef SLOW_HOVER_HPP
#define SLOW_HOVER_HPP

#include "collision.hpp"

class Hover : public Component {
public:
  Hover(Component* p) : Component(p) 
  { 
    _add(new Collision(this));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case MOUSE_HOVER:
        _broadcast(Message(this, IS_COLLISION, msg.data<Rect>()));
        break;

      case COLLISION_TRUE:
        _self->message(Message(this, HOVER));
        break;

      case COLLISION_FALSE:
        _self->message(Message(this, UNHOVER));
        break;

      default:
        _broadcast(msg);
        break;
    }
  }

protected:

};

#endif
