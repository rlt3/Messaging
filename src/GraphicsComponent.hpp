#ifndef SLOW_GRAPHICS_COMPONENT_HPP
#define SLOW_GRAPHICS_COMPONENT_HPP

#include "Graphics.hpp"
#include "Component.hpp"
#include "Coordinate.hpp"

class GraphicsComponent : public Component, protected Graphics {
public:
  GraphicsComponent(float x, float y, int red, int green, int blue, 
                    Messageable *e, Messageable *r) 
    : _position(x, y)
    , _direction(Coordinate::by_direction(SOUTH))
    , Component(e, r)
    , Graphics(e)
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
        _position = msg.data<Coordinate>();
        break;

      case MOVE:
        _direction = Coordinate::by_direction(msg.data<Direction>());
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
    r.x = _position.x;
    r.y = _position.y;
    r.w = 50;
    r.h = 50;

    SDL_RenderFillRect(Graphics::_renderer, &r);
  }

  Coordinate _position;
  Coordinate _direction;

  int _r;
  int _g;
  int _b;
};

#endif
