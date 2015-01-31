#ifndef SLOW_SOUNDBITE_HPP
#define SLOW_SOUNDBITE_HPP

#include "sound.hpp"
#include "component.hpp"

class Soundbite : public Component {
public:
  Soundbite(Component* s) : Component(s)
  {
    sound_init();

    footstep = load_sound_effect("footstep.ogg");
    sword_slash = load_sound_effect("knifeSlice.ogg");
    bonk = load_sound_effect("bonk.ogg");
    elapsed_time = 0;
  }

  ~Soundbite()
  {
    free_sound_effect(footstep);
    free_sound_effect(sword_slash);
    free_sound_effect(bonk);
  }

  void message(const Message &msg)
  {
    switch (msg.type)
    {
      case UPDATE:
        elapsed_time += msg.data<uint32_t>();
        break;

      case HIT:
        break;

      case MOVE:
        do_effect(footstep);
        break;

      case cATTACK:
        do_effect(sword_slash);
        break;
    }
  }

protected:
  Sound_Effect footstep;
  Sound_Effect sword_slash;
  Sound_Effect bonk;

  uint32_t elapsed_time;

  void do_effect(Sound_Effect e)
  {
    if (elapsed_time >= 250)
    {
      elapsed_time = 0;
      play_effect(e);
    }
  }

};


#endif
