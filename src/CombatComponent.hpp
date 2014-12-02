#ifndef SLOW_COMBATCOMPONENT_HPP
#define SLOW_COMBATCOMPONENT_HPP

#include "Component.hpp"
#include "Bullet.hpp"
#include "Monster.hpp"

class CombatComponent : public Component {
public:
  CombatComponent(float x, float y, Messageable *e, Messageable *r) 
    : _direction(Coordinate::by_direction(SOUTH))
    , _position(x, y)
    , Component(e, r)
  { }

  void message(const Message &msg)
  {
    switch (msg.type) {
      case ACTION:
        _room->message(Message(_self, ADD,
            new Bullet(_room, 
              (_direction.x * 50) + _position.x, 
              (_direction.y * 50) + _position.y, 
               _direction)));
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
  }

protected:

  Coordinate _direction;
  Coordinate _position;
};

#endif
