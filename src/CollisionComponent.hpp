#ifndef SLOW_COLLISIONCOMPONENT_HPP
#define SLOW_COLLISIONCOMPONENT_HPP

#include "Component.hpp"

class CollisionComponent : public Component {
public:
  CollisionComponent(float x, float y, Messageable *e, Messageable *r) 
    : _position(x, y) 
    , Component(e, r)
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case MOVEMENT:
        _collision_detect(msg.sender, msg.data<Coordinate>());
        break;

      case POSITION:
        _position = msg.data<Coordinate>();
        break;

      case ATTACK:
        break;

      case HIT:
        break;

      default:
        break;
    }
  }

protected:
  void _collision_detect(Messageable *other, Coordinate c)
  {
    if (_position.x < c.x + 50 &&
        _position.x + 50 > c.x &&
        _position.y < c.y + 50 &&
        _position.y + 50 > c.y) {
      other->message(Message(_self, COLLIDE));
    }
  }

  Coordinate _position;
};

#endif

