#ifndef SLOW_GRAPHICS_COMPONENT_HPP
#define SLOW_GRAPHICS_COMPONENT_HPP

#include "Graphics.hpp"
#include "Component.hpp"
#include "Body.hpp"

class GraphicsComponent : public Component, protected Graphics {
public:
  GraphicsComponent(Body b, int red, int green, int blue, 
                    Messageable *self, Messageable *room) 
    : _body(b)
    , Component(self, room)
    , Graphics(self)
    , _r(red)
    , _g(green)
    , _b(blue) 
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
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
  void _draw()
  {
    SDL_SetRenderDrawColor(Graphics::_renderer, _r, _g, _b, 255);

    SDL_Rect r;
    r.x = _body.position.x;
    r.y = _body.position.y;
    r.w = _body.w;
    r.h = _body.h;

    SDL_RenderFillRect(Graphics::_renderer, &r);
  }

  Body _body;

  int _r;
  int _g;
  int _b;
};

#endif
