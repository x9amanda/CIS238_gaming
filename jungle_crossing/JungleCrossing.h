#include "SDL.h"
#include <SDL_image.h>
#include <string>

class JungleCrossing
{
public:
  JungleCrossing(); // empty default constructor

  // Initialize the game
  bool Initialize();

  // Run the game loop until the game is over
  void RunLoop();

  // Shut down the game when it ends
  void Shutdown();

private:
  // Helper functions for the game loop
  SDL_Texture *LoadTexture(const std::string& fileName);
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();

  // Member data
  SDL_Window *mWindow;     // Window created by SDL2 Lib
  SDL_Renderer *mRenderer; // Renderer for 2D drawing
  Uint32 mTicksCount;      // Number of ticks since the start of the game
  bool mIsRunning;         // Flag for if game should continue to run

  // Jungle Crossing specific member data
  SDL_Texture *mRabbitTexture;
  SDL_Texture *mPantherTexture;
  SDL_Texture *mSnakeTexture;
  SDL_Texture *mMonkeyTexture;
  SDL_Texture *mCrocTexture;

  // Define positions and other necessary variables for the actors
};