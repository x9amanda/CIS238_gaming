#include "JungleCrossing.h"

int
main(int argc, char* argv[])
{
  JungleCrossing game; // puts the game into the CPU

  if (game.Initialize()) {
    game.RunLoop();
  };

  game.Shutdown();

  return 0; // not needed in c++
}