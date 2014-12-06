#ifndef SLOW_BODY_HPP
#define SLOW_BODY_HPP

#include "Coordinate.hpp"

/*
 * Instead of taking an X & Y coordinate, entities simply take a body component
 * instead. 
 *
 * There is no state held in the Entity itself, but each component uses the
 * body for its own needs. 
 *
 * The position of the body is upated through messages through the entity's
 * self.
 */

struct Body {
  int w;
  int h;
  Coordinate position;
  Coordinate magnitude;
  Coordinate direction;

  Body() : w(0), h(0), position(), magnitude(), direction() { }

  Body(int w, int h, float x, float y) 
    : w(w)
    , h(h)
    , position(x, y) 
    , magnitude(0, 0)
    , direction(Coordinate::by_direction(EAST))
  { }
};

#endif
