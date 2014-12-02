#ifndef SLOW_BULLET_HPP
#define SLOW_BULLET_HPP

#include "Entity.hpp"

#include "GraphicsComponent.hpp"
#include "ProjectileComponent.hpp"
#include "CollisionComponent.hpp"

class Bullet : public Entity {
public:
  Bullet(Messageable *room, float x, float y, Coordinate direction) 
    : Entity(room, "Bullet")
  { 
    _messageables.push_back(new GraphicsComponent(x, y, 255, 0, 0, this, room));
    _messageables.push_back(new ProjectileComponent(x, y, direction, 15, this, room));
    _messageables.push_back(new CollisionComponent(x, y, this, room));
  }
};

#endif

