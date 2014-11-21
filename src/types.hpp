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

  /* Between Entities */
  MOVEMENT,
  COLLIDE,
  ATTACK,
  HIT,
  DAMAGE
};

enum Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT
};

#endif
