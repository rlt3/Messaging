#ifndef SLOW_VECTORCOMPONENT_HPP
#define SLOW_VECTORCOMPONENT_HPP

#include "Component.hpp"

class VectorComponent : public Component {
public:
  VectorComponent(Coordinate *c, Messageable *e, Messageable *r) 
    : Component(e, r), _position(c)
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case MOVE:
        //std::cout << "Moving " << _self->name << "." << std::endl;
        _move(msg.data<Direction>());
        break;

      case COLLIDE:
        /* just change direction 180 degrees for collision when vector is built */
        *_position = _last_position;
        break;

      default:
        break;
    }
  }

protected:
  void _move(Direction dir)
  {
    _last_position = *_position;

    switch (dir) {
      case UP:
        *_position = Coordinate(_position->x, _position->y - 1);
        break;
      case RIGHT:
        *_position = Coordinate(_position->x + 1, _position->y);
        break;
      case DOWN:
        *_position = Coordinate(_position->x, _position->y + 1);
        break;
      case LEFT:
        *_position = Coordinate(_position->x - 1, _position->y);
        break;
    }

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

  Coordinate *_position;
  Coordinate _last_position;

  /* 
   * Vector holds direction and only takes input on whether or not we're moving
   * or not. Even if we're not moving, we still face that direction.
   *
   * Or, maybe, the body class (which all Entities have) should contain 
   * direction within itself.
   */
  Direction _direction;

  /*
   * There is T for units of movement  per second elapsed. N is time in seconds.
   * So, if one second has passed and the player has T = 3, then the player has
   * moved 3 units.
   *
   * This delta time lets us update independently so we do not have to keep a
   * separate timestamp for each module (component).
   *
   * This is basically interpolation. This lets us update normally (30 fps) 
   * without having to constantly send update messages to this component. It can
   * interpolate its position from time itself.
   *
   * next_step = current_position + (Direction * Time [N] * Speed [T]);
   */

  uint8_t _magnitude;  // Current speed up to T
  uint8_t _speed;      // <= T
};

#endif
