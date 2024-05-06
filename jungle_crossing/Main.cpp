// Include necessary headers
#include "JungleCrossing.h"

// Define the main function
int main(int argc, char *argv[])
// Instantiate the game object
{
  JungleCrossing game;
  // Initialize the game
  // If initialization succeeds
  if (game.Initialize())
  // Run the game loop
  {
    game.RunLoop();
  };
  // Shutdown the game
  game.Shutdown();
  // Return 0 to indicate successful execution
  return 0;
}