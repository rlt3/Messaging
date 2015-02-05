#ifndef CLICKABLE_HPP
#define CLICKABLE_HPP

#include "collision.hpp"

class Clickable : public Stream {
public:
  Clickable(int id, Stream* up) : Stream(up, this) 
  { 
    _add(new Collision(id, this));
  }

  void message(const Message &msg)
  {
    switch (msg.type)
    {
      case MOUSE_CLICK:
        downstream(IS_COLLISION, msg.data<Rect>());
        break;

      case MOUSE_UNCLICK:
        upstream(UNCLICKED);
        break;

      case COLLISION_TRUE:
        upstream(CLICKED);
        break;

      default:
        downstream(msg);
    }
  }

};

#endif
