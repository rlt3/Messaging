#include <iostream>

#include "Player.hpp"
#include "Monster.hpp"
#include "Room.hpp"

int main()
{
  Room room;

  room.add(new Player(&room, "Stanley"));
  room.add(new Monster(&room, "Ben"));

  room.message(Message(&room, UPDATE));

  return 0;
}
