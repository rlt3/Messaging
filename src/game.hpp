#ifndef SLOW_GAME_HPP
#define SLOW_GAME_HPP

#include "menu.hpp"
#include "room.hpp"

class Game : public Component {
public:
  Game() : Component(), loop_pointer(0)
  {
    loops[0] = new Menu(this);
    loops[1] = new Room(this);

    /* so the vector takes care of the lifetime of the object */
    _add(loops[0]);
    _add(loops[1]);
  }

  void message(const Message &msg)
  {
    switch (msg.type)
    {
      case INPUT:
        handle_input(msg.data<int>());
        break;

      case START:
        loop_pointer = 1;
        break;

      default:
        loops[loop_pointer]->message(msg);
        break;
    }
  }

protected:
  Component *loops[2];
  short unsigned int loop_pointer;

  void handle_input(int key)
  {
    switch(key)
    {
      case ESC_KEY:
        loop_pointer = 0;
        break;
    }
  }
};

#endif
