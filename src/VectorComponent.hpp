#ifndef SLOW_VECTORCOMPONENT_HPP
#define SLOW_VECTORCOMPONENT_HPP

#include "Component.hpp"

class VectorComponent : public Component {
public:
  VectorComponent(Coordinate *c, int speed, Messageable *e, Messageable *r) 
    : Component(e, r), _force(0, 0), _position(c), _max_speed(speed)
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        _move(msg.data<uint32_t>());
        break;

      case MOVE:
        printf("(%f, %f) + (%f, %f) => (%f, %f)\n", 
          _force.x, _force.y,
          force_by_input(msg.data<Input_t>()).x,
          force_by_input(msg.data<Input_t>()).y,
          _force.x, _force.y);
    
        _or_force(force_by_input(msg.data<Input_t>()));
        break;

      case STOP:
        _force = Coordinate(0, 0);
        break;

        /*
         * When colliding, we need to have our magnitude (not direction as that
         * is our guiding force), be manipulated into moving us backwards 
         * temporarily. Perhaps just multiplying by 2 and then inversing the
         * x and y is enough.
         */
      case COLLIDE:
        _magnitude.x = -(_magnitude.x * 2);
        _magnitude.y = -(_magnitude.y * 2);
        break;

      default:
        break;
    }
  }

protected:

  void _or_force(Coordinate dir)
  {
    Coordinate r;
    r.x = (int)_force.x | (int)dir.x;
    r.y = (int)_force.y | (int)dir.y;
    _force = r;
  }

  void _move(uint32_t dt)
  {
    _oscilate();
    _room->message(Message(_self, MOVEMENT, *_position));
  }

  void _oscilate() 
  {
    _magnitude.x = oscilate_ordinate(_force.x, _magnitude.x);
    _magnitude.y = oscilate_ordinate(_force.y, _magnitude.y);
    *_position   = Coordinate::add(*_position, _magnitude);
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

  static Coordinate force_by_input(Input_t input)
  {
    switch(input) {
      case UP :
        return Coordinate(0, -1);

      case RIGHT :
        return Coordinate(1, 0);

      case DOWN :
        return Coordinate(0, 1);

      case LEFT :
        return Coordinate(-1, 0);

      default:
        return Coordinate(0, 0);
    }
  }

  Coordinate *_position; /* current position */
  Coordinate _force;     /* force object is being pushed */
  Coordinate _magnitude; /* current magnitude of object */

  uint8_t _max_speed;
};

#endif
