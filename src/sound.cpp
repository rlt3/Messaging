#include "sound.hpp"

void sound_init()
{
  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
  {
    printf("Sound could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
  }
}

void sound_close()
{
	Mix_Quit();
}

Sound_Effect load_sound_effect(const char *file)
{
	Sound_Effect e = Mix_LoadWAV(file);

  if (e == NULL)
    printf("Failed to load sound effect. %s\n", Mix_GetError());

  return e;
}

Sound_Music load_sound_music(const char *file)
{
	Sound_Music m = Mix_LoadMUS(file);

  if (m == NULL)
    printf("Failed to load music. %s\n", Mix_GetError());

  return m;
}

void play_effect(Sound_Effect e)
{
  Mix_PlayChannel( -1, e, 0 );
}

void free_sound_effect(Sound_Effect e)
{
  Mix_FreeChunk(e);
  e = NULL;
}

void free_sound_music(Sound_Music m)
{
  Mix_FreeMusic(m);
  m = NULL;
}
