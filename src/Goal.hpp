#ifndef SLOW_GOAL_HPP
#define SLOW_GOAL_HPP

#include "Entity.hpp"

#include "GoalGraphicsComponent.hpp"
#include "GoalCollision.hpp"

class Goal : public Entity {
public:
  Goal(Messageable *room, int x, int y, Body b) 
    : Entity(room, "Goal")
  { 
    b.direction = Coordinate::by_direction(WEST);

    _messageables.push_back(new GoalGraphicsComponent(x, y, this, room));
    _messageables.push_back(new GoalCollisionComponent(b, this, room));
  }
};

#endif
