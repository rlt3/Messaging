#ifndef SLOW_MONSTER_HPP
#define SLOW_MONSTER_HPP

#include "Entity.hpp"

#include "GraphicsComponent.hpp"
#include "HealthComponent.hpp"
#include "VectorComponent.hpp"
#include "CollisionComponent.hpp"

class Monster : public Entity {
public:
  Monster(Broadcaster<Entity> *room, float x, float y) 
    : Entity(room, x, y, "Monster")
  { 
    _messageables.push_back(new GraphicsComponent(&_position, 0, 0, 0, this, room));
    _messageables.push_back(new VectorComponent(this, room));
    _messageables.push_back(new HealthComponent(this, room));
    _messageables.push_back(new CollisionComponent(this, room));
  }
};

#endif
