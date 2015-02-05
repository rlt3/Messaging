#ifndef HOVER_HPP
#define HOVER_HPP

#include "collision.hpp"

class Hover : public Stream {
public:
  Hover(int id, Stream* up) : Stream(up, this) 
  { 
    _add(new Collision(id, this));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case MOUSE_HOVER:
        downstream(IS_COLLISION, msg.data<Rect>());
        break;

      case COLLISION_TRUE:
        upstream(HOVER);
        break;

      case COLLISION_FALSE:
        upstream(UNHOVER);
        break;

      default:
        downstream(msg);
        break;
    }
  }

protected:

};

#endif
