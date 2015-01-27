#ifndef SLOW_ROOM_HPP
#define SLOW_ROOM_HPP

#include "tile.hpp"

class Room : public Component {
public:
  Room(Component *p) : Component(p) 
  {
    _add(new Tile(this));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case PLACE:
        _add(msg.data<Component*>());
        break;

      default:
        _broadcast(msg);
        break;
    }
  }
};

#endif
