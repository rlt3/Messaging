#ifndef SLOW_COORDINATE
#define SLOW_COORDINATE

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

  static Coordinate by_direction(Direction d)
  {
    switch(d) {
      case NORTH :
        return Coordinate(0, -1);

      case NORTHEAST : 
        return Coordinate(1, -1);

      case EAST :
        return Coordinate(1, 0);

      case SOUTHEAST : 
        return Coordinate(1, 1);

      case SOUTH :
        return Coordinate(0, 1);

      case SOUTHWEST : 
        return Coordinate(-1, 1);

      case WEST :
        return Coordinate(-1, 0);

      case NORTHWEST :
        return Coordinate(-1, -1);

      default:
        return Coordinate(0, 0);
    }
  }
};

#endif
