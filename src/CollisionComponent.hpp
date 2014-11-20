#ifndef SLOW_COLLISIONCOMPONENT_HPP
#define SLOW_COLLISIONCOMPONENT_HPP

#include "Component.hpp"

class CollisionComponent : public Component {
public:
  CollisionComponent(Messageable *e, Messageable *r) 
    : Component(e, r) 
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case MOVEMENT:
        std::cout << _self->name << " was bumped by " << msg.sender->name << "." << std::endl;
        _room->message(Message(_self, COLLIDE));
        break;

      case ATTACK:
        if (msg.sender == _self) {
          std::cout << "Message from self." << std::endl;
        }

        std::cout << _self->name << " was attacked by " << msg.sender->name << "." << std::endl;
        _room->message(Message(_self, HIT));
        break;

      case HIT:
        std::cout << _self->name << " hit " << msg.sender->name << "." << std::endl;
        _room->message(Message(_self, DAMAGE, 10));
        break;

      default:
        break;
    }
  }
};

#endif

