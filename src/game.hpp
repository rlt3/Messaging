#ifndef SLOW_GAME_HPP
#define SLOW_GAME_HPP

#include "menu.hpp"
#include "room.hpp"

class Game : public Component {
public:
  Game() : Component(), pointer(0)
  {
    _add(new Menu(this));
    _add(new Room(this));
  }

  void message(const Message &msg)
  {
    /*
     * TODO:
     *  - Some sort of `curtain' which uses alpha transparency that goes from
     *  255 to 0 over a set period of time allowing for all other components
     *  to `work' normally until the curtain is `drawn', effectively changing
     *  the scene.
     *
     *  So, we would like to be able to see the button being pushed down for a
     *  brief period before starting the game. 
     */

    switch (msg.type)
    {
      case START:
        pointer = 1;
        break;

      case PAUSE:
        pointer = 0;
        break;

      default:
        /* use the std::vector's [] overloading to access element n */
        _components[pointer]->message(msg);
        break;
    }
  }

protected:
  short unsigned int pointer;

};

#endif
