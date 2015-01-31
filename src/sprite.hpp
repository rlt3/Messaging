
/*
 * Remember:
 *  First frame is default or `idle'.
 *
 *  Might be able to get by with just displaying the first frame of the weapon
 *  state (direction) overlayed over the walking animation of the character.
 *
 *  But the attack animation needs to be unison with the weapon and the player
 *  attack animation.
 */

#ifndef SLOW_SPRITE_HPP
#define SLOW_SPRITE_HPP

#include "component.hpp"
#include "graphics.hpp"

class Sprite : public Component {
public:

  /* 
   * rules is a rect: x, y, w, h. The x, y is the offset it would normally
   * be drawn. 0, 0 for no offset. w, h is the width and height of the
   * sprite given.
   */

  /* constructor with given sprite rules */
  Sprite(Rect rules, const char *spritefile, Component* s) 
    : Component(s) 
    , x_offset(rules.x)
    , y_offset(rules.y)
    , width(rules.w)
    , height(rules.h)
    , state(0)
    , frame(0)
    , animating(false)
    , elapsed_time(0)
    , position(rect(0, 0, width, height))
    , sprite(load_sprite(spritefile))
  { 
    max_frames = texture_width(sprite) / width;
  }

  /* constructor which assume default sprite rules */
  Sprite(const char *spritefile, Component* s) 
    : Component(s) 
    , x_offset(0)
    , y_offset(0)
    , width(SPRITE_SIZE)
    , height(SPRITE_SIZE)
    , state(0)
    , frame(0)
    , animating(false)
    , elapsed_time(0)
    , position(rect(0, 0, width, height))
    , sprite(load_sprite(spritefile))
  { 
    max_frames = texture_width(sprite) / width;
  }

  ~Sprite()
  {
    destroy_texture(sprite);
  }

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
        set_position(msg.data<Rect>());
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
  int x_offset;
  int y_offset;
  int width;
  int height;

  int state;
  int frame;
  int max_frames;
  bool animating;

  uint32_t elapsed_time;

  Rect position;

  Spritesheet sprite;

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
      _self->message(Message(_self, ANIMATION_DONE, state));

      /*
       * add in ANIMATION_INTERRUPTED message so that various things can react
       * to an interrupted action. Like interrupting a spell cast might cause
       * a spell failed sound and also cancel the action.
       */
    }
  }

  /* if animating, bump frame to 1 to get everything started since 0 is idle */
  void animate(int s)
  {
    /* interrupt for a different animation */
    if (state != s || !animating) 
    {
      state     = s;
      frame     = 1;
      animating = true;
    }
  }

  /* if there is an explicit state set, stop animation and put frame to 0 */
  void set_state(int s)
  {
    state     = s;
    frame     = 0;
    animating = false;
  }

  /* 
   * Use the offsets to get the final draw position. Also, use internal width
   * and height so that everything else can just worry about x, y without 
   * worrying about w, h.
   */
  void set_position(Rect r)
  {
    position.x = r.x + x_offset;
    position.y = r.y + y_offset;
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
