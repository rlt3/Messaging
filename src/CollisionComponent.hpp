#ifndef SLOW_COLLISIONCOMPONENT_HPP
#define SLOW_COLLISIONCOMPONENT_HPP

#include "Component.hpp"

class CollisionComponent : public Component {
public:
  CollisionComponent(Messageable *m) : _entity(m) { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case MOVEMENT:
        std::cout << _entity->name << " was bumped by " << msg.sender->name << "." << std::endl;
        broadcast(_entity, Message(_entity, COLLIDE));

      case ATTACK:
        std::cout << _entity->name << " was hit by " << msg.sender->name << "." << std::endl;
        broadcast(_entity, Message(_entity, HIT));

      default:
        break;
    }
  }

protected:
  Messageable *_entity;

};

#endif

