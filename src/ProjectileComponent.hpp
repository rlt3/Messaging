#ifndef SLOW_PROJECTILECOMPONENT_HPP
#define SLOW_PROJECTILECOMPONENT_HPP

#include "Component.hpp"
#include "Body.hpp"

class ProjectileComponent : public Component {
public:
  ProjectileComponent(Body b, int speed, Messageable *e, Messageable *r) 
    : Component(e, r), _body(b)
  { 
    /* set the magnitude, based on direction and speed, which stays constant */
    _body.magnitude = Coordinate::multiply(_body.direction, speed);
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
    _body.position = Coordinate::add(_body.position, _body.magnitude);
    _room->message(Message(_self, MOVEMENT, _body));
    _self->message(Message(_self, POSITION, _body));
  }

  void _collision(Body other) 
  {
    /* use other body's magnitude so we can slice the ball, etc */
    _body.magnitude.x = -(_body.magnitude.x);
    _body.magnitude.y = -(_body.magnitude.y);
  }

  Body _body;
};

#endif
