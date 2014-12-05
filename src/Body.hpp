#ifndef SLOW_BODY_HPP
#define SLOW_BODY_HPP

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
  int x;
  int y;
};

#endif
