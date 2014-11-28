#ifndef SLOW_TYPES_HPP
#define SLOW_TYPES_HPP

enum message_t {
  /* From System */
  START,
  QUIT,
  UPDATE, 
  INPUT,
  RENDER,
  DRAW,

  /* Within Entity */
  MOVE,
  STOP,

  /* Between Entities */
  MOVEMENT,
  COLLIDE,
  ATTACK,
  HIT,
  DAMAGE
};

enum Input_t {
  UP,
  RIGHT,
  DOWN,
  LEFT,
  USE
};

enum State_t {
  MOVING,
  IDLE,
};

#endif
