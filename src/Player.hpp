#ifndef SLOW_PLAYER_HPP
#define SLOW_PLAYER_HPP

#include "Entity.hpp"

#include "InputComponent.hpp"
#include "HealthComponent.hpp"
#include "VectorComponent.hpp"
#include "CollisionComponent.hpp"

class Player : public Entity {
public:
  Player(Broadcaster<Entity> *room, std::string s) : Entity(room, s)
  { 
    _messageables.push_back(new InputComponent(this, room));
    _messageables.push_back(new VectorComponent(this, room));
    _messageables.push_back(new HealthComponent(this, room));
    _messageables.push_back(new CollisionComponent(this, room));
  }
};

#endif
