#ifndef SLOW_ROOM_HPP
#define SLOW_ROOM_HPP

/*
 * Room holds a list of entities and acts as an observer for messages. Entities
 * notify the room, which then notifies all entities in the room.
 */

#include <algorithm>
#include <vector>
#include "messageable.hpp"

class Entity;

typedef std::vector<Entity*>::iterator Entity_Iterator;

class Room : public Messageable {
public:
  Room();
  ~Room();

  void message(Message msg);

protected:
  void add_entity();
  void remove_entity(Entity *entity);

  std::vector<Entity*> _entities;
};

#endif
