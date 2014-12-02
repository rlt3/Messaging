#ifndef SLOW_VECTORCOMPONENT_HPP
#define SLOW_VECTORCOMPONENT_HPP

#include "Component.hpp"

class VectorComponent : public Component {
public:
  VectorComponent(float x, float y, int speed, Messageable *e, Messageable *r) 
    : _position(x, y)
    , _max_speed(speed)
    , _force(0, 0)
    , Component(e, r)
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        _move(msg.data<uint32_t>());
        break;

      /* Apply a force in the direction of input */
      case MOVE:
        _force = Coordinate::by_direction(msg.data<Direction>());
        break;

      /* Set no force if we're stopping */
      case STOP:
        _force = Coordinate(0, 0);
        break;

      /* Based on our magnitude, bounce backwards off the object */
      case COLLIDE:
        _magnitude.x = -(_magnitude.x * 2);
        _magnitude.y = -(_magnitude.y * 2);
        break;

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
    _room->message(Message(_self, MOVEMENT, _position));
    _self->message(Message(_self, POSITION, _position));
  }

  /* handle the speed up of an entity and its forces */
  void _oscilate() 
  {
    _magnitude.x = oscilate_ordinate(_force.x, _magnitude.x);
    _magnitude.y = oscilate_ordinate(_force.y, _magnitude.y);
    _position    = Coordinate::add(_position, _magnitude);
  }

  float oscilate_ordinate(float force, float current) 
  {
    /* if there is a force and not max speed, add the force */
    if (force != 0.0f && abs(current) <= _max_speed) {
      return (current + force);
    } else {
    /* else bring current toward 0 from whatever direction (neg or pos) */
      if (current == 0.0f) 
        return current;
      else
        return (current + ((current < 0.0f) ? 1 : -1));
    }
  }

  Coordinate _position; /* current position */
  Coordinate _force;     /* force object is being pushed */
  Coordinate _magnitude; /* current magnitude of object */

  uint8_t _max_speed;
};

#endif
