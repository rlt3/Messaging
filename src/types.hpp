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

  ADD,
  DEATH,

  SCORE,

  /* Within Entity */
  MOVE,     /* turn entity */
  STOP,     /* stop entity */
  POSITION, /* update position */
  ACTION,   /* do entity's action */

  /* Between Entities */
  MOVEMENT,
  COLLIDE,
  ATTACK,
  HIT,
  DAMAGE
};

enum Direction {
  NORTH,
  NORTHEAST,
  EAST,
  SOUTHEAST,
  SOUTH,
  SOUTHWEST,
  WEST,
  NORTHWEST
};

enum State_t {
  MOVING,
  IDLE,
};

#endif
