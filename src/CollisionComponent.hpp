#ifndef SLOW_COLLISIONCOMPONENT_HPP
#define SLOW_COLLISIONCOMPONENT_HPP

#include "Component.hpp"

class CollisionComponent : public Component {
public:
  CollisionComponent(Coordinate *c, Messageable *e, Messageable *r) 
    : Component(e, r), _position(c) 
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case MOVEMENT:
        //std::cout << _self->name << " was bumped by " << msg.sender->name << "." << std::endl;
        _collision_detect(msg.sender, msg.data<Coordinate>());
        break;

      case ATTACK:
        //if (msg.sender == _self) {
        //  std::cout << "Message from self." << std::endl;
        //}

        //std::cout << _self->name << " was attacked by " << msg.sender->name << "." << std::endl;
        //_room->message(Message(_self, HIT));
        break;

      case HIT:
        //std::cout << _self->name << " hit " << msg.sender->name << "." << std::endl;
        //_room->message(Message(_self, DAMAGE, 10));
        break;

      default:
        break;
    }
  }

protected:
  void _collision_detect(Messageable *other, Coordinate c)
  {
/*
    var rect1 = {x: 5, y: 5, width: 50, height: 50}
    var rect2 = {x: 20, y: 10, width: 10, height: 10}

    if (rect1.x < rect2.x + rect2.width &&
       rect1.x + rect1.width > rect2.x &&
       rect1.y < rect2.y + rect2.height &&
       rect1.height + rect1.y > rect2.y) {
        // collision detected!
    }
*/

    if (_position->x < c.x + 50 &&
        _position->x + 50 > c.x &&
        _position->y < c.y + 50 &&
        _position->y + 50 > c.y) {
      other->message(Message(_self, COLLIDE));
    }
  }

  Coordinate *_position;
};

#endif

