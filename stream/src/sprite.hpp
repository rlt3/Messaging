#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "entity.hpp"
#include "graphics.hpp"
#include "stream.hpp"

class Sprite : public Stream
{
public:
  Sprite(int id, Stream *up) 
    : Stream(up, this)
    , id(id)
    , state(0)
    , frame(0)
    , max_frames(num_sprite_frames(id))
    , animating(false)
    , elapsed_time(0)
    , position(point(0, 0))
  { }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case UPDATE:
        update(msg.data<uint32_t>());
        break;

      case DRAW:
        draw();
        break;

      case POSITION:
        position = msg.data<Point>();
        break;

        /* animate the given state */
      case ANIMATE:
        animate(msg.data<int>());
        break;

        /* update the given state, interrupting animations */
      case STATE:
        set_state(msg.data<int>());
        break;
    }
  }

protected:
  int id;

  int state;
  int frame;
  int max_frames;

  bool animating;

  uint32_t elapsed_time;

  Point position;

  void update(uint32_t dt)
  {
    elapsed_time += dt;

    if (animating && elapsed_time >= FRAME_TIME)
    {
      elapsed_time = 0;
      frame = ++frame % max_frames;
    }

    /* 0 is our idle frame, so if we're there then we're done */
    if (frame == 0 && animating)
    {
      animating = false;
      upstream(ANIMATION_DONE, state);
    }
  }

  /* if animating, bump frame to 1 to get everything started since 0 is idle */
  void animate(int s)
  {
    /* interrupt for a different animation */
    if (state != s || !animating) 
    {
      handle_interrupt();
      state     = s;
      frame     = 1;
      animating = true;
    }
  }

  /* if there is an explicit state set, stop animation and put frame to 0 */
  void set_state(int s)
  {
    handle_interrupt();
    state     = s;
    frame     = 0;
    animating = false;
  }

  void handle_interrupt()
  {
    if (animating)
      upstream(ANIMATION_INTERRUPTED, state);
  }

  void draw()
  {
    draw_sprite(id, state, frame, position);
  }
};

#endif
