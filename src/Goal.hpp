#ifndef SLOW_GOAL_HPP
#define SLOW_GOAL_HPP

/*
 * The paddle for pong.
 */

#include "Entity.hpp"

#include "GraphicsComponent.hpp"
#include "CollisionComponent.hpp"

class Goal : public Entity {
public:
  Goal(Messageable *room, Body b) 
    : Entity(room, "Goal")
  { 
    _messageables.push_back(new GraphicsComponent(b, 255, 255, 255, this, room));
    _messageables.push_back(new CollisionComponent(b, this, room));
  }
};

#endif
