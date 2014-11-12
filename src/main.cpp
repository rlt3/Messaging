#include "game.hpp"

int
main()
{
  Game game;

  game.message(Message(&game, LOCATE));
  game.message(Message(&game, MOVEMENT, LEFT));
  game.message(Message(&game, MOVEMENT, RIGHT));
  game.message(Message(&game, MOVEMENT, DOWN));
  game.message(Message(&game, LOCATE));

  return 0;
}
