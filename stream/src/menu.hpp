#ifndef MENU_HPP
#define MENU_HPP

#include "menu_item.hpp"

class Menu : public Stream {
public:
  Menu(Stream* up) : Stream(up, this)
  {
    _add(new MenuItem(this));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case START:
        upstream(START);
        break;

      default:
        downstream(msg);
    }
  }
};

#endif
