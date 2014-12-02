#ifndef SLOW_MONSTER_HPP
#define SLOW_MONSTER_HPP

#include "Entity.hpp"

#include "GraphicsComponent.hpp"
#include "HealthComponent.hpp"
#include "CollisionComponent.hpp"

class Monster : public Entity {
public:
  Monster(Broadcaster<Entity> *room, float x, float y) 
    : Entity(room, "Monster")
  { 
    _messageables.push_back(new GraphicsComponent(x, y, 0, 0, 0, this, room));
    _messageables.push_back(new CollisionComponent(x, y, this, room));
    _messageables.push_back(new HealthComponent(this, room));
  }
};

#endif
