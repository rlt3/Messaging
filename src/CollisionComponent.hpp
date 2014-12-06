#ifndef SLOW_COLLISIONCOMPONENT_HPP
#define SLOW_COLLISIONCOMPONENT_HPP

#include "Component.hpp"
#include "Body.hpp"

class CollisionComponent : public Component {
public:
  CollisionComponent(Body b, Messageable *self, Messageable *room) 
    : _body(b)
    , Component(self, room)
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case MOVEMENT:
        _collision_detect(msg.sender, msg.data<Body>());
        break;

      case POSITION:
        _body = msg.data<Body>();
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
  void _collision_detect(Messageable *other, Body b)
  {
    if (_body.position.x < b.position.x + b.w &&
        _body.position.x + _body.w > b.position.x &&
        _body.position.y < b.position.y + b.h &&
        _body.position.y + _body.h > b.position.y) {
      other->message(Message(_self, COLLIDE, _body));
    }
  }

  Body _body;
};

#endif

