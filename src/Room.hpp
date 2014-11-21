#ifndef SLOW_ROOM_HPP
#define SLOW_ROOM_HPP

#include "Entity.hpp"
#include "Player.hpp"
#include "Monster.hpp"

class Room : public Broadcaster<Entity> {
public:
  Room(Messageable *e) : _game(e), Broadcaster<Entity>() 
  { 
    add(new Player(this, 10, 10));
    add(new Monster(this, 75, 75));
  }

  ~Room() { }

  Entity* add(Entity *e)
  {
    _messageables.push_back(e);
    return e;
  }

private:
  Messageable *_game;
};

#endif
