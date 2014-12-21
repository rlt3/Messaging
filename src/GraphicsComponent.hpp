#ifndef SLOW_GRAPHICS_COMPONENT_HPP
#define SLOW_GRAPHICS_COMPONENT_HPP

#include "Graphics.hpp"
#include "Component.hpp"
#include "Body.hpp"

#include <queue>

class GraphicsComponent : public Component, protected Graphics {
public:
  GraphicsComponent(Body b, int red, int green, int blue, 
                    Messageable *self, Messageable *room) 
    : _body(b)
    , _elasped_time(0)
    , Component(self, room)
    , Graphics(self)
    , _r(red)
    , _g(green)
    , _b(blue) 
  { 
    _animations.push(_walk_frame());
  }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        _update(msg.data<uint32_t>());
        break;

      case DRAW:
        _draw();
        break;
        
      case POSITION:
        _body = msg.data<Body>();
        break;

      default:
        break;
    }
  }

protected:

  /* pop the animation frame queue and push state-based frame if empty */
  void _update(const uint32_t dt)
  {
    _elasped_time += dt;

    if (_elasped_time >= 250) {
      _elasped_time = 0;

      if (!_animations.empty()) {
        _animations.pop();
      }

      if (_animations.empty()) {
        _animations.push(_walk_frame());
      }
    }
  }

  SDL_Color _walk_frame() {
    static bool odd = true;

    SDL_Color s;

    if (odd) {
      s.r = 0;
      s.g = 255;
      s.b = 0;
      odd = false;

    } else {
      s.r = 255;
      s.g = 0;
      s.b = 0;
      odd = true;

    }

    return s;
  }

  void _draw()
  {
    SDL_Color color = _animations.front();
    SDL_SetRenderDrawColor(Graphics::_renderer, 
        color.r, 
        color.g, 
        color.b, 
        255);

    SDL_Rect r;
    r.x = _body.position.x;
    r.y = _body.position.y;
    r.w = _body.w;
    r.h = _body.h;

    SDL_RenderFillRect(Graphics::_renderer, &r);
  }

  /*
   * TODO:
   *  `flip' between red & green to simulate walking frames.
   *
   *  On bounce, push a series of three colors to display.
   */

  std::queue<SDL_Color> _animations;

  uint32_t _elasped_time;

  Body _body;

  int _r;
  int _g;
  int _b;
};

#endif
