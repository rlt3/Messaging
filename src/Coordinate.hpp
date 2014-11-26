#ifndef SLOW_COORDINATE
#define SLOW_COORDINATE

struct Coordinate {
  float x;
  float y;

  Coordinate() : x(0), y(0) { }
  Coordinate(float x, float y) : x(x), y(y) { }

  static Coordinate add(const Coordinate &l, const Coordinate &r) {
    return Coordinate(l.x + r.x, l.y + r.y);
  }

  static Coordinate add(const Coordinate &l, const float &scale) {
    return Coordinate(l.x + scale, l.y + scale);
  }

  static Coordinate multiply(const Coordinate &l, const Coordinate &r) {
    return Coordinate(l.x * r.x, l.y * r.y);
  }

  static Coordinate multiply(const Coordinate &l, const float &scale) {
    return Coordinate(l.x * scale, l.y * scale);
  }

  //void add(const Coordinate &rhs) {
  //  x += rhs.x;
  //  y += rhs.y;
  //}

  //void add(const float &scale) {
  //  x += scale;
  //  y += scale;
  //}

  //void multiply(const Coordinate &rhs) {
  //  x *= rhs.x;
  //  y *= rhs.y;
  //}

  //void multiply(const float &scale) {
  //  x *= scale;
  //  y *= scale;
  //}
};

#endif
