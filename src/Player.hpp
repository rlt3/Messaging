#ifndef SLOW_PLAYER_HPP
#define SLOW_PLAYER_HPP

#include "Entity.hpp"

#include "GraphicsComponent.hpp"
#include "InputComponent.hpp"
#include "HealthComponent.hpp"
#include "VectorComponent.hpp"
#include "CollisionComponent.hpp"
#include "CombatComponent.hpp"

class Player : public Entity {
public:
  Player(Messageable *room, float x, float y) 
    : Entity(room, "Player")
  { 
    _messageables.push_back(new GraphicsComponent(x, y, 255, 255, 255, this, room));
    _messageables.push_back(new VectorComponent(x, y, 10, this, room));
    _messageables.push_back(new CollisionComponent(x, y, this, room));
    _messageables.push_back(new CombatComponent(x, y, this, room));
    _messageables.push_back(new InputComponent(this, room));
    _messageables.push_back(new HealthComponent(this, room));
  }
};

#endif
