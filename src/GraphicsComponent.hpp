#ifndef SLOW_GRAPHICS_COMPONENT_HPP
#define SLOW_GRAPHICS_COMPONENT_HPP

#include "Graphics.hpp"
#include "Component.hpp"
#include "Coordinate.hpp"

class GraphicsComponent : public Component, protected Graphics {
public:
  GraphicsComponent(Coordinate *p, int red, int grn, int blu, 
                    Messageable *e, Messageable *r) 
    : _position(p)
    , Component(e, r)
    , Graphics(e)
    , _r(red)
    , _g(grn)
    , _b(blu) 
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case DRAW:
        _draw();
        break;

      default:
        break;
    }
  }

protected:
  void _draw()
  {
    SDL_SetRenderDrawColor(Graphics::_renderer, _r, _g, _b, 255);

    SDL_Rect r;
    r.x = _position->x;
    r.y = _position->y;
    r.w = 50;
    r.h = 50;

    SDL_RenderFillRect(Graphics::_renderer, &r);
  }

  Coordinate *_position;

  int _r;
  int _g;
  int _b;
};

#endif
