#ifndef DATA_STRUCTS_HPP
#define DATA_STRUCTS_HPP

struct Rect
{
  int x;
  int y;
  int w;
  int h;
};

struct Point
{
  int x;
  int y;
};

inline Rect rect(int x, int y, int w, int h)
{
  return { x, y, w, h };
}

inline Point point(int x, int y)
{
  return { x, y };
}

#endif
