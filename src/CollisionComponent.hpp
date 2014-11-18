#ifndef SLOW_COLLISIONCOMPONENT_HPP
#define SLOW_COLLISIONCOMPONENT_HPP

#include "Component.hpp"

class CollisionComponent : public Component {
public:
  CollisionComponent(Messageable *m) : Component(m) { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case MOVEMENT:
        std::cout << _entity->name << " was bumped by " << msg.sender->name << "." << std::endl;
        broadcast(Message(_entity, COLLIDE));
        break;

      case ATTACK:
        if (msg.sender == _entity) {
          std::cout << "Message from self." << std::endl;
        }

        std::cout << _entity->name << " was attacked by " << msg.sender->name << "." << std::endl;
        broadcast(Message(_entity, HIT));
        break;

      case HIT:
        std::cout << _entity->name << " hit " << msg.sender->name << "." << std::endl;
        broadcast(Message(_entity, DAMAGE, 10));
        break;

      default:
        break;
    }
  }
};

#endif

