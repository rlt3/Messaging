#ifndef SLOW_GAME_HPP
#define SLOW_GAME_HPP

#define ONE_SECOND       1000
#define THIRTY_FPS       (ONE_SECOND/30)
#define FIFTEEN_FPS      (ONE_SECOND/15)


#include <iostream>

#include "Broadcaster.hpp"
#include "Graphics.hpp"
#include "Input.hpp"
#include "Room.hpp"

class Game : public Broadcaster<Messageable> {
public:
  Game();

  void message(const Message &msg);

protected:
  void _loop();

  bool     _running;
  uint32_t _current_time;
  uint32_t _last_time;
};

#endif
