#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

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
  SDL_Texture* LoadTexture(const std::string& fileName);
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();
  void RenderText();

  bool CheckCollision();
  bool CheckCollisions();

// Instantiate the Carrot class object
      Carrot mCarrot; 


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

      // Background textures
    SDL_Texture *mJungleTexture;
    SDL_Texture *mMeadowTexture;

  // Define positions and other necessary variables for the actors
  int mRabbitDir;          // Direction of the rabbit
  Vector2 mRabbitPos;      // Position of the rabbit
  Vector2 mPantherPos;     // Position of the panther
  Vector2 mSnakePos;       // Position of the snake
  Vector2 mMonkeyPos;      // Position of the monkey
  Vector2 mCrocPos;   // Position of the crocodile

    // Define positions and sizes for the background textures
    SDL_Rect mJungleRect;
    SDL_Rect mMeadowRect;
};