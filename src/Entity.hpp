#ifndef SLOW_ENTITY_HPP
#define SLOW_ENTITY_HPP

#include "Broadcaster.hpp"
#include "Component.hpp"
#include "Coordinate.hpp"

class Entity : public Broadcaster<Component> {
public:
  Entity(Broadcaster<Entity> *room, float x, float y, std::string s) 
    : Broadcaster<Component>()
    , _room(room)
    , _position(Coordinate(x, y))
    , _state(IDLE)
  { 
    name = s;
  }

  ~Entity() { }

protected:
  Broadcaster<Entity> *_room;
  Coordinate           _position;
  State_t              _state;
};

#endif
