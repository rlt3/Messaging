#ifndef SLOW_ENTITY_HPP
#define SLOW_ENTITY_HPP

#include "room.hpp"
#include "messageable.hpp"
#include "state.hpp"
#include "coordinate.hpp"

#include "graphics_component.hpp"
#include "input_component.hpp"

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
    , _input(this)
    , _graphics(&_coordinates)
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case ATTACK: 
      case LOCATION:
      case MOVEMENT:
        break;

      case UPDATE:
        _input.message(Message(this, UPDATE));
        break;

      case DRAW:
        _graphics.message(Message(this, DRAW));
        break;

      case MOVE:
        _move(msg.data<Direction>());
        break;

      case LOCATE:
        notify(msg.sender, Message(this, LOCATION, _coordinates));
        break;

      default:
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
        _coordinates = Coordinate(_coordinates.x, _coordinates.y - 1);
        break;

      case RIGHT:
        _coordinates = Coordinate(_coordinates.x + 1, _coordinates.y);
        break;

      case DOWN:
        _coordinates = Coordinate(_coordinates.x, _coordinates.y + 1);
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

  /* TODO: Generic container for n components all of which receive messages */
  Graphics_Component _graphics;
  Input_Component    _input;

  /*
   * Instead of a component list, how about a generic Entity class template 
   * (this) and just inherit it and then define private components for there.
   *
   * So, a player wouldn't have an AI component, but a Monster would. Doing it
   * this way would make it easier to generate random Entities (monsters/items/
   * whatever) by switch statements. If you made lists, you would have to create
   * the list, add the components, and then construct the entity rather than
   * just do Monster(10, 10) or Item(50, 6)
   */
};

#endif
