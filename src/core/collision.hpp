#ifndef SLOW_COLLISION_HPP
#define SLOW_COLLISION_HPP

#include "component.hpp"
#include "sdl_bindings.hpp"

class Collision : public Component {
public:
  Collision(Component* p) : Component(p) 
  { 
    _body = { 0, 0, SPRITE, SPRITE };
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {

      /*
       * May handle extra like:
       *  POINT_INSIDE -
       *  for gui (cursor) interaction among other things
       */

      case IS_COLLISION:
        _check_collision(msg.data<Rect>());
        break;

      case POSITION:
        _body = msg.data<Rect>();
        break;
    }
  }

protected:

  Rect _body;

  void _check_collision(Rect r)
  {
    if (_collision_at(r))
      _parent->message(Message(this, COLLISION_TRUE));
    else
      _parent->message(Message(this, COLLISION_FALSE));
  }

  bool _collision_at(Rect r)
  {
    return (_body.x < r.x + r.w &&
            _body.x + _body.w > r.x &&
            _body.y < r.y + r.h &&
            _body.y + _body.h > r.y);
  }

};

#endif
