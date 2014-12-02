#ifndef SLOW_PROJECTILECOMPONENT_HPP
#define SLOW_PROJECTILECOMPONENT_HPP

#include "Component.hpp"

class ProjectileComponent : public Component {
public:
  ProjectileComponent(float x, float y, Coordinate direction, int speed, 
                      Messageable *e, Messageable *r) 
    : Component(e, r), _position(x, y)
  { 
    /* set the magnitude, based on direction and speed, which stays constant */
    _magnitude = Coordinate::multiply(direction, speed);
  }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        _move(msg.data<uint32_t>());
        break;

      case COLLIDE:
        msg.sender->message(Message(_self, DAMAGE, 10));
        _magnitude = Coordinate(0, 0);
        break;

      default:
        break;
    }
  }

protected:

  /* move entity and broadcast the new position */
  void _move(uint32_t dt)
  {
    _position = Coordinate::add(_position, _magnitude);
    _room->message(Message(_self, MOVEMENT, _position));
    _self->message(Message(_self, POSITION, _position));
  }

  Coordinate _position; 
  Coordinate _magnitude;
};

#endif

