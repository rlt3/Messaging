#ifndef SLOW_ENTITY_HPP
#define SLOW_ENTITY_HPP

#include "room.hpp"
#include "messageable.hpp"
#include "state.hpp"
#include "coordinate.hpp"

/*
 * Entities are things like monsters, objects, or the player. They handle things
 * like collision on an individual basis. Simply overloading a method makes it
 * easy to create unique monsters/items/whatever. 
 */

class Entity : public Messageable {
public:
  Entity(entity_t type, Room *room, float x, float y)
    : _state(IDLE)
    , _type(type)
    , _coordinates(x, y)
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case ATTACK: 
      case LOCATION:
        break;

      case MOVEMENT:
        _move(msg.data<Direction>());
        break;

      case LOCATE:
        notify(msg.sender, Message(this, LOCATION, _coordinates));
        break;
    }
  }

protected:

  /* broadcast message to room */
  void broadcast(const Message &msg) 
  {
    this->notify(_room, msg);
  }

  void _move(Direction direction)
  {
    switch(direction) {
      case UP:
        _coordinates = Coordinate(_coordinates.x, _coordinates.y + 1);
        break;

      case RIGHT:
        _coordinates = Coordinate(_coordinates.x + 1, _coordinates.y);
        break;

      case DOWN:
        _coordinates = Coordinate(_coordinates.x, _coordinates.y - 1);
        break;

      case LEFT:
        _coordinates = Coordinate(_coordinates.x - 1, _coordinates.y);
        break;
    }
  }

  entity_t    _type;
  State       _state;
  Coordinate  _coordinates;
  Room       *_room;
};

#endif
