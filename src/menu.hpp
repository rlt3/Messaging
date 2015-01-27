#ifndef SLOW_MENU_HPP
#define SLOW_MENU_HPP

#include "menu_item.hpp"
#include "pointer.hpp"

class Menu : public Component {
public:
  Menu(Component* s) : Component(s)
  {
    _add(new MenuItem(this));
    _add(new Pointer(this));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case START:
        _self->message(msg);
        break;

      default:
        _broadcast(msg);
    }
  }
};

#endif
