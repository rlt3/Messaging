#ifndef SLOW_TYPES_HPP
#define SLOW_TYPES_HPP

enum entity_t {
  PLAYER,
  MONSTER
};

enum message_t {
  BROADCAST,
  UPDATE,
  ATTACK,
  DRAW,
  MOVE,
  MOVEMENT,
  LOCATE,
  LOCATION
};

enum Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT
};

enum State {
  IDLE,
  FLEE
};

#endif
