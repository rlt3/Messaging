#ifndef SLOW_ROOM_HPP
#define SLOW_ROOM_HPP

#include "Entity.hpp"
#include "Player.hpp"
#include "Monster.hpp"

class Room : public Broadcaster<Entity> {
public:
  Room(Messageable *e) : _game(e), Broadcaster<Entity>() 
  { 
    add(new Player(this, 300, 220));
    add(new Monster(this, 300, 300));
  }

  ~Room() { }

private:
  Messageable *_game;
};

#endif
