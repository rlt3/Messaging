#ifndef SLOW_GOAL_HPP
#define SLOW_GOAL_HPP

/*
 * The paddle for pong.
 */

#include "Entity.hpp"

#include "GraphicsComponent.hpp"
#include "BarVectorComponent.hpp"
#include "BarCollisionComponent.hpp"
#include "InputComponent.hpp"

/* player1Input, player2Input */

class Goal : public Entity {
public:
  Goal(Messageable *room, float x, float y) 
    : Entity(room, "Goal")
  { 
    _messageables.push_back(new GraphicsComponent(x, y, 255, 255, 255, this, room));
    _messageables.push_back(new PaddleVectorComponent(x, y, 10, this, room));
    _messageables.push_back(new PaddleCollisionComponent(x, y, this, room));
    _messageables.push_back(new InputComponent(this, room));
  }
};

#endif

