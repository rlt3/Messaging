#ifndef SLOW_COLLISION_HPP
#define SLOW_COLLISION_HPP

#include "stream.hpp"
#include "graphics.hpp"

class Collision : public Stream {
public:
  Collision(int id, Stream* up) 
    : Stream(up, this) 
    , body(sprite_size(id))
  { }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case IS_COLLISION:
        check_collision(msg.data<Rect>());
        break;

      case POSITION:
        update_position(msg.data<Point>());
        break;
    }
  }

protected:

  Rect body;

  void update_position(Point p)
  {
    body.x = p.x;
    body.y = p.y;
  }

  void check_collision(Rect r)
  {
    if (collision_at(r))
      upstream(COLLISION_TRUE);
    else
      upstream(COLLISION_FALSE);
  }

  bool collision_at(Rect r)
  {
    return (body.x < r.x + r.w &&
            body.x + body.w > r.x &&
            body.y < r.y + r.h &&
            body.y + body.h > r.y);
  }

};

#endif
