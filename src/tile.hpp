#ifndef SLOW_TILE_HPP
#define SLOW_TILE_HPP

#include "component.hpp"
#include "graphics.hpp"

class Tile : public Component {
public:
  Tile(Component* s) : Component(s)
  {
    floor     = load_sprite("floor.png");

    top_left  = load_sprite("wall-top-left.png");
    top_right = load_sprite("wall-top-right.png");
    mid_top   = load_sprite("wall-top-middle.png");
    mid_left  = load_sprite("wall-middle-left.png");
    mid_right = load_sprite("wall-middle-right.png");
  }

  ~Tile()
  {
    destroy_texture(floor);

    destroy_texture(top_left);
    destroy_texture(top_right);
    destroy_texture(mid_top);
    destroy_texture(mid_left);
    destroy_texture(mid_right);

  }

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
  Spritesheet floor;

  Spritesheet top_left;
  Spritesheet top_right;
  Spritesheet mid_top;
  Spritesheet mid_left;
  Spritesheet mid_right;

  void draw()
  {
    int x, y;

    int y_height = WINDOW_HEIGHT / SPRITE_SIZE;
    int x_width  = WINDOW_WIDTH  / SPRITE_SIZE;

    Rect location;

    for (y = 0; y < y_height; y++)
    {
      for (x = 0; x < x_width; x++)
      {
        location = { SPRITE_SIZE * x, SPRITE_SIZE * y, SPRITE_SIZE, SPRITE_SIZE };

        if ((y == 0 && x == 0)) {
          draw_sprite(top_left, location);

        } else if (y == 0 && x == (x_width - 1)) {
          draw_sprite(top_right, location);

        } else if (y == 0) {
          draw_sprite(mid_top, location);

        } else if (x == 0) {
          draw_sprite(mid_left, location);

        } else if (x == (x_width - 1)) {
          draw_sprite(mid_right, location);

        } else {
          draw_sprite(floor, location);
        }

      }
    }
  }
};

#endif
