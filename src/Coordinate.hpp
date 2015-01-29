#ifndef SLOW_COORDINATE
#define SLOW_COORDINATE

#include "entity_state.hpp"

struct Coordinate {
  float x;
  float y;

  Coordinate() : x(0), y(0) { }
  Coordinate(float x, float y) : x(x), y(y) { }

  static float dot(const Coordinate &l, const Coordinate &r) {
    return (l.x * r.x) + (l.y * r.y);
  }

  static Coordinate add(const Coordinate &l, const Coordinate &r) {
    return Coordinate(l.x + r.x, l.y + r.y);
  }

  static Coordinate add(const Coordinate &l, const float &scale) {
    return Coordinate(l.x + scale, l.y + scale);
  }

  static Coordinate sub(const Coordinate &l, const Coordinate &r) {
    return Coordinate(l.x - r.x, l.y - r.y);
  }

  static Coordinate multiply(const Coordinate &l, const Coordinate &r) {
    return Coordinate(l.x * r.x, l.y * r.y);
  }

  static Coordinate scale(const float &scale, const Coordinate &l) {
    return Coordinate(l.x * scale, l.y * scale);
  }

  static Coordinate by_state(int state)
  {
    switch(state) {
      case MOVE_DOWN:  /* down  */
        return Coordinate(0, 1);

      case MOVE_RIGHT:  /* right */
        return Coordinate(1, 0);

      case MOVE_UP:  /* up    */
        return Coordinate(0, -1);

      case MOVE_LEFT:  /* left  */
        return Coordinate(-1, 0);
    }

    return Coordinate(0, 0);
  }
};

#endif
