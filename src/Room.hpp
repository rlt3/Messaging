#ifndef SLOW_ROOM_HPP
#define SLOW_ROOM_HPP

#include "Entity.hpp"

class Room : public Broadcaster<Entity> {
public:
  Room() : Broadcaster<Entity>() { }
  ~Room() { }

  Entity* add(Entity *e)
  {
    _messageables.push_back(e);
    return e;
  }
};

#endif
