#include "Game.hpp"

int main()
{
  Game game;

  game.message(Message(&game, START));

  return 0;
}
