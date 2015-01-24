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
        _parent->message(Message(this, STATE, 1));
        break;

      case COLLISION_FALSE:
        _parent->message(Message(this, STATE, 0));
        break;

      default:
        _broadcast(msg);
        break;
    }
  }

protected:

};

#endif
