#ifndef SLOW_ENTITY_HPP
#define SLOW_ENTITY_HPP

#include "messageable.hpp"
#include "coordinate.hpp"
#include "room.hpp"
#include "graphics.hpp"

class Game : public Messageable {
public:
  Game();
  ~Game();

  void message(const Message &msg);
  void render();
  void update();

protected:
  Messageable *_room;
  Graphics     _graphics;
};

#endif
