#ifndef SLOW_DRAG_HPP
#define SLOW_DRAG_HPP

#include "collision.hpp"

class Drag : public Component {
public:
  Drag(Component* p) : Component(p) 
  { 
    _clicked = false;
    _add(new Collision(this));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case MOUSE_HOVER:
        if (_clicked)
          _parent->message(Message(_parent, POSITION, msg.data<Rect>()));
        break;

      case MOUSE_CLICK:
        _broadcast(Message(this, IS_COLLISION, msg.data<Rect>()));
        break;

      case MOUSE_UNCLICK:
        _parent->message(Message(this, STATE, 0));
        _clicked = false;
        break;

      case COLLISION_TRUE:
        _parent->message(Message(this, STATE, 2));
        _clicked = true;
        break;

      default:
        _broadcast(msg);
        break;
    }
  }

protected:
  bool _clicked;

};

#endif
