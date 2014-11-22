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

  Coordinate *_position;
  Coordinate _last_position;
};

#endif
