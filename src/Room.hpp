#ifndef SLOW_ROOM_HPP
#define SLOW_ROOM_HPP

#include "Entity.hpp"
#include "Player.hpp"
#include "Monster.hpp"

class Room : public Broadcaster<Entity> {
public:
  Room(Messageable *e) : _game(e), Broadcaster<Entity>() 
  { 
    _add(new Player(this, 300, 220));
    _add(new Monster(this, 300, 300));
  }

  ~Room() { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case ADD:
        _add(msg.data<Entity*>());
        break;

      case DEATH:
        _remove((Entity*) msg.sender);
        break;

      default:
        _broadcast(msg);
        break;
    }
  }

private:
  Messageable *_game;
};

#endif
