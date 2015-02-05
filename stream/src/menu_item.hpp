#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include "clickable.hpp"
#include "sprite.hpp"
#include "hover.hpp"

class MenuItem : public Stream {
public:
  MenuItem(Stream* up) : Stream(up, this)
  {
    _add(new Clickable(MENU_BUTTON, this));
    _add(new Hover(MENU_BUTTON, this));
    _add(new Sprite(MENU_BUTTON, this));

    /* set the position */
    downstream(POSITION, point(300, 300));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case HOVER:
        downstream(STATE, 1);
        break;

      case UNHOVER:
        downstream(STATE, 0);
        break;

      case CLICKED:
        upstream(START);
        break;

      default:
        downstream(msg);
        break;
    }
  }
};

#endif

