#ifndef SLOW_ENTITY_HPP
#define SLOW_ENTITY_HPP

#include "messageable.hpp"
#include "coordinate.hpp"
#include "room.hpp"

class Game : public Messageable {
public:
  Game();
  ~Game();

  void message(const Message &msg);

protected:
  Messageable *_room;
};

#endif
