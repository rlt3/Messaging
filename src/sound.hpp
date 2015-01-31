#ifndef SLOW_SOUND_HPP
#define SLOW_SOUND_HPP

#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

typedef Mix_Chunk* Sound_Effect;
typedef Mix_Music* Sound_Music;

void sound_init();
void sound_close();

Sound_Effect load_sound_effect(const char *file);
Sound_Music  load_sound_music(const char *file);

void play_effect(Sound_Effect e);

void free_sound_effect(Sound_Effect e);
void free_sound_music(Sound_Music m);

#endif
