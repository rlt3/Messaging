#ifndef TILE_HPP
#define TILE_HPP

#include "stream.hpp"
#include "graphics.hpp"

class Tile : public Stream {
public:
  Tile(Stream* up) : Stream(up, this)
  { }

  void message (const Message &msg)
  {
    switch (msg.type)
    {
      case DRAW:
        draw();
        break;
    }
  }

protected:

  void draw()
  {
    int x, y;

    int y_height = WINDOW_HEIGHT / SPRITE_SIZE;
    int x_width  = WINDOW_WIDTH  / SPRITE_SIZE;

    Point location;

    for (y = 0; y < y_height; y++)
    {
      for (x = 0; x < x_width; x++)
      {
        location = { x * SPRITE_SIZE, y * SPRITE_SIZE };

        if ((y == 0 && x == 0)) {
          draw_sprite(TILE_TOP_LEFT, location);

        } else if (y == 0 && x == (x_width - 1)) {
          draw_sprite(TILE_TOP_RIGHT, location);

        } else if (y == 0) {
          draw_sprite(TILE_MID_TOP, location);

        } else if (x == 0) {
          draw_sprite(TILE_MID_LEFT, location);

        } else if (x == (x_width - 1)) {
          draw_sprite(TILE_MID_RIGHT, location);

        } else {
          draw_sprite(TILE_FLOOR, location);
        }

      }
    }
  }
};

#endif
