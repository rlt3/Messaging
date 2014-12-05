#ifndef SLOW_PADDLE_HPP
#define SLOW_PADDLE_HPP

/*
 * The paddle for pong.
 */

#include "Entity.hpp"

#include "GraphicsComponent.hpp"
#include "BarVectorComponent.hpp"
#include "BarCollisionComponent.hpp"
#include "InputComponent.hpp"

/* player1Input, player2Input */

class Paddle : public Entity {
public:
  Player(Messageable *room, float x, float y) 
    : Entity(room, "Paddle")
  { 
    _messageables.push_back(new GraphicsComponent(x, y, 255, 255, 255, this, room));
    _messageables.push_back(new PaddleVectorComponent(x, y, 10, this, room));
    _messageables.push_back(new PaddleCollisionComponent(x, y, this, room));
    _messageables.push_back(new InputComponent(this, room));
  }
};

#endif
