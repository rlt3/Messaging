#ifndef SLOW_ENTITY_HPP
#define SLOW_ENTITY_HPP

#include "Broadcaster.hpp"
#include "Component.hpp"
#include "Coordinate.hpp"

class Entity : public Broadcaster<Component> {
public:
  Entity(Messageable *room, std::string s) 
    : Broadcaster<Component>()
    , _room(room)
  { 
    name = s;
  }

  ~Entity() { }

protected:
  Messageable *_room;
};

#endif
