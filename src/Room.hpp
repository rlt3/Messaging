#ifndef SLOW_ROOM_HPP
#define SLOW_ROOM_HPP

#include "Entity.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Goal.hpp"
#include "Wall.hpp"

class Room : public Broadcaster<Entity> {
public:
  Room(Messageable *e) : _game(e), Broadcaster<Entity>() 
  { 
    _add(new Paddle(this, Body(20, 100, 30, 275)));
    _add(new Paddle(this, Body(20, 100, 750, 275)));

    _add(new Goal(this, 110, 10, Body(20, 600, -20, 0)));
    _add(new Goal(this, 590, 10, Body(20, 600, 800, 0)));

    _add(new Wall(this, Body(800, 20, 0, -20)));
    _add(new Wall(this, Body(800, 20, 0, 600)));

    _add(new Ball(this, Body(20, 20, 400, 300)));
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
