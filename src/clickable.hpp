#ifndef SLOW_CLICKABLE_HPP
#define SLOW_CLICKABLE_HPP

#include "collision.hpp"

class Clickable : public Component {
public:
  Clickable(Component* p) : Component(p) 
  { 
    _add(new Collision(this));
  }

  void message(const Message &msg)
  {
    switch (msg.type)
    {
      case MOUSE_CLICK:
        _broadcast(Message(this, IS_COLLISION, msg.data<Rect>()));
        break;

      case MOUSE_UNCLICK:
        _self->message(Message(this, UNCLICKED));
        break;

      case COLLISION_TRUE:
        _self->message(Message(this, CLICKED));
        break;

      default:
        _broadcast(msg);
    }
  }

};

#endif
