#ifndef SLOW_ENTITY_HPP
#define SLOW_ENTITY_HPP

#include "Broadcaster.hpp"
#include "Component.hpp"

class Entity : public Broadcaster<Component> {
public:
  Entity(Broadcaster<Entity> *room, std::string s) 
    : Broadcaster<Component>(), _room(room)
  { 
    name = s;
  }

  ~Entity() { }

protected:
  Broadcaster<Entity> *_room;
};

#endif
