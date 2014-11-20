#ifndef SLOW_MONSTER_HPP
#define SLOW_MONSTER_HPP

#include "Entity.hpp"

#include "HealthComponent.hpp"
#include "VectorComponent.hpp"
#include "CollisionComponent.hpp"

class Monster : public Entity {
public:
  Monster(Broadcaster<Entity> *room, std::string s) : Entity(room, s)
  { 
    _messageables.push_back(new VectorComponent(this, room));
    _messageables.push_back(new HealthComponent(this, room));
    _messageables.push_back(new CollisionComponent(this, room));
  }
};

#endif
