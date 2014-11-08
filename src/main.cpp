#include "game.hpp"

int
main()
{
  Game game;

  Message move_left(MOVEMENT, &game, Coordinate(10, 10), (int) LEFT);
  Message move_right(MOVEMENT, &game, Coordinate(10, 10), (int) RIGHT);
  Message move_down(MOVEMENT, &game, Coordinate(10, 10), (int) DOWN);
  Message find(LOCATE, &game, Coordinate(10, 10), 0);

  game.message(find);
  game.message(move_left);
  game.message(move_right);
  game.message(move_down);
  game.message(find);

  return 0;
}
