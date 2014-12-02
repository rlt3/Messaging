#ifndef SLOW_PLAYER_HPP
#define SLOW_PLAYER_HPP

#include "Entity.hpp"

#include "GraphicsComponent.hpp"
#include "InputComponent.hpp"
#include "HealthComponent.hpp"
#include "VectorComponent.hpp"
#include "CollisionComponent.hpp"

#include "Bullet.hpp"

class Player : public Entity {
public:
  Player(Broadcaster<Entity> *room, float x, float y) 
    : Entity(room, "Player")
    , _direction(Coordinate::by_direction(SOUTH))
    , _position(x, y)
  { 
    _messageables.push_back(new GraphicsComponent(x, y, 255, 255, 255, this, room));
    _messageables.push_back(new VectorComponent(x, y, 10, this, room));
    _messageables.push_back(new CollisionComponent(x, y, this, room));
    _messageables.push_back(new InputComponent(this, room));
    _messageables.push_back(new HealthComponent(this, room));
  }

  void message(const Message &msg)
  {
    switch (msg.type) {
      case ACTION:
        printf("shooting ...\n");
        _room->add(new Bullet(_room, _position.x, _position.y, _direction));
        break;

      case POSITION:
        _position = msg.data<Coordinate>();
        break;

      case MOVE:
        _direction = Coordinate::by_direction(msg.data<Direction>());
        break;

      default:
        break;
    }

    _broadcast(msg);
  }

protected:

  Coordinate _direction;
  Coordinate _position;
};

#endif
