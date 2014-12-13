#ifndef SLOW_GOAL_GRAPHICS_COMPONENT_HPP
#define SLOW_GOAL_GRAPHICS_COMPONENT_HPP

#include "Graphics.hpp"
#include "Component.hpp"
#include "Body.hpp"

#include <SDL2_ttf/SDL_ttf.h>

class GoalGraphicsComponent : public Component, protected Graphics {
public:
  GoalGraphicsComponent(int x, int y, Messageable *self, Messageable *room) 
    : x(x)
    , y(y)
    , Component(self, room)
    , Graphics(self)
    , score(-1)
    , surface(NULL)
    , text(NULL)
  { 
    if (TTF_Init() == -1) {
      printf("TTF_Init: %s\n", TTF_GetError());
      exit(2);
    }
    
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    font = TTF_OpenFont("Verdana.ttf", 24);

    if (!font) {
      printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    
    _update_score();
  }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case DRAW:
        _draw();
        break;

      case SCORE:
        _update_score();
        break;

      default:
        break;
    }
  }

protected:
  void _draw()
  {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = 96;
    r.h = 96;

    SDL_RenderCopy(Graphics::_renderer, text, NULL, &r);
  }

  void _update_score() {
    score++;

    if (surface != NULL) {
      SDL_FreeSurface(surface);
    }

    if (text != NULL) {
      SDL_DestroyTexture(text);
    }

    surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), color);
    text    = SDL_CreateTextureFromSurface(Graphics::_renderer, surface);
  }

  int x;
  int y;

  int score;

  TTF_Font  *font;
  SDL_Color  color;

  SDL_Surface *surface;
  SDL_Texture *text;
};

#endif
