#ifndef SLOW_ENTITY_HPP
#define SLOW_ENTITY_HPP

#include "messageable.hpp"
#include "room.hpp"

class Game : public Messageable {
public:
  Game();
  ~Game();

  void message(Message msg);

protected:
  Messageable *_room;
};

#endif
