#ifndef SLOW_WALL_HPP
#define SLOW_WALL_HPP

#include "Entity.hpp"
#include "CollisionComponent.hpp"

class Wall : public Entity {
public:
  Wall(Messageable *room, Body b) 
    : Entity(room, "Goal")
  { 
    b.direction = Coordinate::by_direction(SOUTH);
    _messageables.push_back(new CollisionComponent(b, this, room));
  }
};

#endif

