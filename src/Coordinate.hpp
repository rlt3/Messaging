#ifndef SLOW_COORDINATE
#define SLOW_COORDINATE

struct Coordinate {
  float x;
  float y;

  Coordinate() : x(0), y(0) { }
  Coordinate(float x, float y) : x(x), y(y) { }
};

#endif
