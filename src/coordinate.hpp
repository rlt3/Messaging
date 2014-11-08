#ifndef SLOW_COORDINATE
#define SLOW_COORDINATE

struct Coordinate {
  float x;
  float y;

  Coordinate() : x(0), y(0) { }
  Coordinate(float x, float y) : x(x), y(y) { }

  /*
  bool operator< (const Coordinate &) const;
  bool operator> (const Coordinate &) const;
  bool operator==(const Coordinate &) const;

  Coordinate& operator+=(const Coordinate &);
  Coordinate& operator*=(const Coordinate &);
  Coordinate& operator-=(const Coordinate &);
  Coordinate& operator+ (const Coordinate &);
  Coordinate& operator* (const Coordinate &);
  Coordinate& operator- (const Coordinate &);

  Coordinate& operator*=(const int &);
  Coordinate& operator+=(const int &);
  Coordinate& operator-=(const int &);
  Coordinate& operator* (const int &);
  Coordinate& operator+ (const int &);
  Coordinate& operator- (const int &);
  */
};

#endif
