#ifndef SLOW_PROJECTILECOMPONENT_HPP
#define SLOW_PROJECTILECOMPONENT_HPP

#include "Component.hpp"
#include "Body.hpp"

class ProjectileComponent : public Component {
public:
  ProjectileComponent(Body b, int speed, Messageable *e, Messageable *r) 
    : Component(e, r), _body(b), _max_speed(speed)
  { 
    /* set the magnitude, based on direction and speed, which stays constant */
    _body.magnitude = Coordinate::scale(_max_speed, _body.direction);
  }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        _move(msg.data<uint32_t>());
        break;

      case COLLIDE:
        _collision(msg.data<Body>());
        break;

      case POSITION:
        _body = msg.data<Body>();
        break;

      default:
        break;
    }
  }

protected:

  /* move entity and broadcast the new position */
  void _move(uint32_t dt)
  {
    _body.magnitude.x = oscilate_ordinate(_body.magnitude.x);
    _body.magnitude.y = oscilate_ordinate(_body.magnitude.y);

    _body.position = Coordinate::add(_body.position, _body.magnitude);

    _room->message(Message(_self, MOVEMENT, _body));
    _self->message(Message(_self, POSITION, _body));
  }

  /* when ball goes over max speed, force it back to normal */
  float oscilate_ordinate(float current) 
  {
    if (abs(current) <= _max_speed || current == 0.0f) {
      return current;
    } else {
      return (current + ((current < 0.0f) ? 1 : -1));
    }
  }

  void _collision(Body other) 
  {
    /* 
     * reflect the current magnitude across the collided body's normal, which
     * simulates `bouncing' at an angle. then add in the other body's magnitude
     * so we can put a spin on the ball.
     *
     * (other * 0.5) + (magnitude - 2 * (magnitude DOT normal) * normal)
     *
     * other is other body's magnitude.
     * magnitude is this body's magnitude.
     * normal is other body's normal
     */

    _body.magnitude = 
      Coordinate::add(
        Coordinate::scale(0.5f, other.magnitude),
        Coordinate::sub(_body.magnitude, Coordinate::scale(2, 
          Coordinate::scale(Coordinate::dot(_body.magnitude, other.direction),
            other.direction))));
  }

  Body _body;
  int  _max_speed;
};

#endif
