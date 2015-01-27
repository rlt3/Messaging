
/*
 * For start: just get offset via Rect { x-offset, y-offset, width, height }
 *
 * This allows to have sprites of any width & height and also allow for offsets,
 * i.e. weapon sprite overlaying.
 */

#ifndef SLOW_SPRITE_HPP
#define SLOW_SPRITE_HPP

#include "component.hpp"
#include "graphics.hpp"

class Sprite : public Component {
public:
  Sprite(Rect rules, const char *spritefile, Component* s) : Component(s) 
  { 
    /* rules is a rect: x, y, w, h. The x, y is the offset it would normally
     * be drawn. 0, 0 for no offset. w, h is the width and height of the
     * sprite given.
     */

    x_offset = rules.x;
    y_offset = rules.y;
    width    = rules.w;
    height   = rules.h;

    state    = 0;
    frame    = 0;

    position = { 0, 0, width, height };

    sprite   = load_sprite(spritefile);
  }

  Sprite(const char *spritefile, Component *s) : Component(s)
  {
    x_offset = 0;
    y_offset = 0;
    width    = SPRITE_SIZE;
    height   = SPRITE_SIZE;

    state    = 0;
    frame    = 0;

    position = { 0, 0, width, height };

    sprite   = load_sprite(spritefile);
  }

  ~Sprite()
  {
    destroy_texture(sprite);
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case DRAW:
        draw();
        break;

      case POSITION:
        set_position(msg.data<Rect>());
        break;

      case STATE:
        state = msg.data<int>();
        break;
    }
  }

protected:
  int x_offset;
  int y_offset;
  int width;
  int height;

  int state;
  int frame;

  Rect position;

  Spritesheet sprite;

  /* 
   * Use the offsets to get the final draw position. Also, use internal width
   * and height so that everything else can just worry about x, y without 
   * worrying about w, h.
   */
  void set_position(Rect r)
  {
    position.x = r.x - x_offset;
    position.y = r.y - y_offset;
    position.w = width;
    position.h = height;
  }

  void draw()
  {
    Rect f = { frame * width, state * height, width, height };
    draw_sprite(sprite, f, position);
  }

};

#endif
