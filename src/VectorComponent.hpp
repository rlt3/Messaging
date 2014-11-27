#ifndef SLOW_VECTORCOMPONENT_HPP
#define SLOW_VECTORCOMPONENT_HPP

#include "Component.hpp"

class VectorComponent : public Component {
public:
  VectorComponent(Coordinate *c, int speed, Messageable *e, Messageable *r) 
    : Component(e, r), _force(0, 0), _position(c), _speed(speed)
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        _move(msg.data<uint32_t>());
        break;

      case MOVE:
        //_force = direction_by_state(msg.data<Direction>());
        
    printf("(%f, %f) + (%f, %f) => (%f, %f)\n", 
        _force.x, _force.y,
        direction_by_state(msg.data<Direction>()).x,
        direction_by_state(msg.data<Direction>()).y,
        _force.x, _force.y);

        _force = direction_by_state(msg.data<Direction>());

        //_force = Coordinate::add(_force, direction_by_state(msg.data<Direction>()));
        break;

      case STOP:
        _force = Coordinate(0, 0);
        break;

        /*
         * When colliding, we need to have our magnitude (not direction as that
         * is our guiding force), be manipulated into moving us backwards 
         * temporarily. Perhaps just multiplying by 2 and then inversing the
         * x and y is enough.
         */
      case COLLIDE:
        _magnitude.x = -(_magnitude.x * 2);
        _magnitude.y = -(_magnitude.y * 2);
        break;

      default:
        break;
    }
  }

protected:

  void stuff(Coordinate dir) {
    /* need to xor the current _force with the new direction's force.
     *
     * this way instead of adding you only get one or zero for either of the
     * two ordinates.
     *
     * exclusive or for positive and negative -- keep sign
     */
  }

  float oscilate_coord(float force, float current) {
    /* if there is a force and not max speed, add the force */
    if (force != 0.0f && abs(current) <= _speed) {
      return (current + force);
    } else {
    /* else bring current toward 0 from whatever direction (neg or pos) */
      if (current == 0.0f) 
        return current;
      else
        return (current + ((current < 0.0f) ? 1 : -1));
    }
  }

  void _oscilate() {
    _magnitude.x = oscilate_coord(_force.x, _magnitude.x);
    _magnitude.y = oscilate_coord(_force.y, _magnitude.y);
    *_position   = Coordinate::add(*_position, _magnitude);
  }

  void _move(uint32_t dt)
  {
    _oscilate();
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
  Coordinate _force;
  Coordinate _magnitude;

  uint8_t _speed;      // <= T
};

#endif
