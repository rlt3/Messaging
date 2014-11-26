#ifndef SLOW_PLAYER_HPP
#define SLOW_PLAYER_HPP

#include "Entity.hpp"

#include "GraphicsComponent.hpp"
#include "InputComponent.hpp"
#include "HealthComponent.hpp"
#include "VectorComponent.hpp"
#include "CollisionComponent.hpp"

class Player : public Entity {
public:
  Player(Broadcaster<Entity> *room, float x, float y) 
    : Entity(room, x, y, "Player")
  { 
    _messageables.push_back(new GraphicsComponent(&_position, 255, 255, 255, this, room));
    _messageables.push_back(new VectorComponent(&_position, &_state, 20, this, room));
    _messageables.push_back(new CollisionComponent(&_position, this, room));
    _messageables.push_back(new InputComponent(this, room));
    _messageables.push_back(new HealthComponent(this, room));
  }

  void message(const Message &msg) {
    switch (msg.type) {
      case MOVE:
        _state = MOVING;
        break;

      case STOP:
        _state = IDLE;
        break;

      default:
        break;
    }
    _broadcast(msg);
  }
};

#endif
