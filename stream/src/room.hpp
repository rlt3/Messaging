#ifndef ROOM_HPP
#define ROOM_HPP

#include "tile.hpp"
#include "player.hpp"
//#include "skeleton.hpp"

class Room : public Stream {
public:
  Room(Stream *up) : Stream(up, this) 
  {
    _add(new Tile(this));
    _add(new Player(this));
    //_add(new Skeleton(this));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case PLACE:
        _add(msg.data<Stream*>());
        break;

      case REMOVE:
        _remove(msg.sender);
        break;

      default:
        downstream(msg);
        break;
    }
  }
};

#endif
