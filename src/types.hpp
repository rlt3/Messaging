#ifndef SLOW_TYPES_HPP
#define SLOW_TYPES_HPP

enum Entity_Type {
  PLAYER,
  MONSTER
};

enum Message_Type {
  ATTACK,
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
  MOVE,
  FLEE
};

#endif
