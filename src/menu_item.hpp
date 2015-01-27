#ifndef SLOW_MENU_ITEM_HPP
#define SLOW_MENU_ITEM_HPP

#include "sprite.hpp"
#include "clickable.hpp"
#include "hover.hpp"

class MenuItem : public Component {
public:
  MenuItem(Component* s) : Component(s)
  {
    _add(new Hover(this));
    _add(new Clickable(this));
    _add(new Sprite(rect(0, 0, 190, 49), "start.png", this));

    /* set the position */
    _broadcast(Message(this, POSITION, rect(300, 300, 190, 49)));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case HOVER:
        _broadcast(Message(this, STATE, 1));
        break;

      case UNHOVER:
        _broadcast(Message(this, STATE, 0));
        break;

      case CLICKED:
        _self->message(Message(this, START));
        break;

      default:
        _broadcast(msg);
        break;
    }
  }
};

#endif
