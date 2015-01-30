#ifndef SLOW_ROOM_HPP
#define SLOW_ROOM_HPP

#include "tile.hpp"
#include "player.hpp"
#include "skeleton.hpp"

class Room : public Component {
public:
  Room(Component *p) : Component(p) 
  {
    _add(new Tile(this));
    _add(new Player(this));
    _add(new Skeleton(this));
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
