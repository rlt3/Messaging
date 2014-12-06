#ifndef SLOW_PADDLE_HPP
#define SLOW_PADDLE_HPP

/*
 * The paddle for pong.
 */

#include "Entity.hpp"

#include "GraphicsComponent.hpp"
#include "CollisionComponent.hpp"
#include "VectorComponent.hpp"
#include "InputComponent.hpp"

/* player1Input, player2Input */

class Paddle : public Entity {
public:
  Paddle(Messageable *room, Body b)
    : Entity(room, "Paddle")
  { 
    _messageables.push_back(new GraphicsComponent(b, 255, 255, 255, this, room));
    _messageables.push_back(new VectorComponent(b, 10, this, room));
    _messageables.push_back(new CollisionComponent(b, this, room));
    _messageables.push_back(new InputComponent(this, room));
  }
};

#endif
