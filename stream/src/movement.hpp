#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "entity.hpp"
#include "stream.hpp"

class Movement: public Stream
{
public:
  Movement(int speed, Stream *up)
    : Stream(up, this)
    , _max_speed(speed)
    , _force(point(0, 0))
    , _body(point(0, 0))
    , _magnitude(point(0, 0))
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        _move(msg.data<uint32_t>());
        break;

      case POSITION:
        _body = msg.data<Point>();
        break;

      /* Apply a force in the direction of input */
      case MOVE:
        _force = force_by_state(msg.data<int>());
        break;

      /* Set no force if we're stopping (we haven't input a force) */
      case STOP:
        _force = point(0, 0);
        break;

      /* Based on our magnitude, bounce backwards off the object */
      //case COLLIDE:
      //  _magnitude.x = -(_magnitude.x * 2);
      //  _magnitude.y = -(_magnitude.y * 2);
      //  break;

      default:
        break;
    }
  }

protected:

  /* move entity and broadcast the new position */
  void _move(uint32_t dt)
  {
    _oscilate();

    /* broadcast to self our new position and to room */
    upstream(POSITION, _body);
    /* might be better as MOVING_TO and then entity above translates downstream
     * as position */
  }

  /* handle the speed up of an entity and its forces */
  void _oscilate() 
  {
    _magnitude.x = oscilate_ordinate(_force.x, _magnitude.x);
    _magnitude.y = oscilate_ordinate(_force.y, _magnitude.y);
    _body = add_points(_body, _magnitude);
  }

  int oscilate_ordinate(int force, int current) 
  {
    /* if there is a force and not max speed, add the force */
    if (force != 0 && abs(current) <= _max_speed) {
      return (current + force);
    } else {
    /* else bring current toward 0 from whatever direction (neg or pos) */
      if (current == 0) 
        return current;
      else
        return (current + ((current < 0) ? 1 : -1));
    }
  }

  Point add_points(Point l, Point r)
  {
    return { l.x + r.x , l.y + r.y };
  }

  Point force_by_state(int state)
  {
    switch(state) {
      case DOWN:
        return point(0, 1);

      case RIGHT:
        return point(1, 0);

      case UP:  
        return point(0, -1);

      case LEFT:
        return point(-1, 0);

      default:
        return point(0, 0);
    }
  }

  Point _body;      /* current position */
  Point _force;     /* force object is being pushed */
  Point _magnitude;

  uint8_t _max_speed;
};

#endif
