#ifndef SLOW_VECTORCOMPONENT_HPP
#define SLOW_VECTORCOMPONENT_HPP

#include "Component.hpp"

class VectorComponent : public Component {
public:
  VectorComponent(Coordinate *c, State *state, int speed, Messageable *e, Messageable *r) 
    : Component(e, r), _position(c), _state(state), _speed(speed)
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        _move(msg.data<uint32_t>());
        break;

      case MOVE:
        _direction = direction_by_state(msg.data<Direction>());
        break;

      case COLLIDE:
        inverse_direction();
        break;

      default:
        break;
    }
  }

protected:
  void _oscilate_magnitude() {
    if(*_state == MOVING && _magnitude <= _speed)
      _magnitude += (_magnitude == _speed) ? 0 : 1;
    else
      _magnitude -= (_magnitude == 0) ? 0 : 1;
  }

  void _move(uint32_t dt)
  {
    _oscilate_magnitude();

    *_position = Coordinate::add(*_position, 
        Coordinate::multiply(_direction, _magnitude));
    
    _room->message(Message(_self, MOVEMENT, *_position));
  }

  static Coordinate direction_by_state(Direction dir) {
    switch(dir) {
      case UP :
        return Coordinate(0, -1);

      case RIGHT :
        return Coordinate(1, 0);

      case DOWN :
        return Coordinate(0, 1);

      case LEFT :
        return Coordinate(-1, 0);

      default:
        return Coordinate(0, 0);
    }
  }

  void inverse_direction() {
    _direction.x = -_direction.x;
    _direction.y = -_direction.y;
  }

  Coordinate *_position;
  Coordinate _direction;

  State *_state;

  /* 
   * Can combine magnitude/speed into a Coordinate which represents the 
   * direction being moved and at what speed. While entity is moving, the
   * magnitude rises to the speed at whatever direction and lower to 0 when
   * not moving.
   *
   * We can use this to set `negative` magnitudes. While having input the
   * magnitude would just oscilate towards that direction. So, if an entity
   * collided at a high speed, the entity would bounce and, if input was still
   * being given, move back towards whatever it bounced off of.
   */

  uint8_t _magnitude;  // Current speed up to T
  uint8_t _speed;      // <= T
};

#endif
