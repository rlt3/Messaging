#ifndef SLOW_GRAPHICS_HPP
#define SLOW_GRAPHICS_HPP

#include "messageable.hpp"
#include <SDL2/SDL.h>

class Graphics : public Messageable {
public:
  Graphics(Messageable *g);
  ~Graphics();

  void message(const Message &msg);

protected:
  static SDL_Renderer     *_renderer;

private:
  static SDL_Window       *_window;
  static SDL_RendererInfo  _renderer_info;
  static bool              _initialized;

  void _clear();
  void _render();
  void _init();
  
  Messageable *_game;

};

#endif
