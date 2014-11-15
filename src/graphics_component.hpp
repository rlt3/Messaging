#ifndef SLOW_GRAPHICS_COMPONENT_HPP
#define SLOW_GRAPHICS_COMPONENT_HPP

#include "graphics.hpp"
#include "coordinate.hpp"

/*
 *      Kami: (To Everything) Draw.
 *    Entity: (To Components) Draw.
 * Component: <renders>
 */

/*
 * Have entity use Position component which then is passed to all other
 * components which need Position (like graphics/vector/etc). Using components
 * like this will make messages homogeneous rather than some types of messages
 * carrying different data (like above).
 */

/*
 * Entity should just be a container for components and the components should
 * really make up the identity. Every entity should have a position (which would
 * be a component), but not every entity is moveable (a vector component). 
 * Both position and vector receive the MOVEMENT message, but only the vector
 * acts on it, even though the vector makes use of the position component itself.
 *
 * Or, maybe, the position isn't a component (since it is so fundamental to
 * many components) and thus doesn't need to accept messages at all. If an 
 * entity isn't moveable, then just pass it's position to the constructor and
 * it won't move again if it doesn't have the vector component.
 */

class Graphics_Component : public Graphics {
public:
  Graphics_Component(Coordinate *c)
    : _position(c)
  { }

  void message(const Message &msg)
  {
    switch (msg.type) {
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
    SDL_SetRenderDrawColor(Graphics::_renderer, 255, 255, 255, 255);

    SDL_Rect r;
    r.x = _position->x;
    r.y = _position->y;
    r.w = 50;
    r.h = 50;

    SDL_RenderFillRect(Graphics::_renderer, &r);
  }


  Coordinate *_position;
};

#endif
