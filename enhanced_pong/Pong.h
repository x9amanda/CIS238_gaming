#include "SDL.h"

struct Vector2
{
  float x;
  float y;
};

class Pong
{
public:
  Pong(); // empty default constructor

  // Initialize the game
  bool Initialize();

  // Run the game loop until the game is over
  void RunLoop();

  // Shut down the game when it ends
  void Shutdown();

private:
  // Helper functions for the game loop
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();

  bool hitPaddle();
  bool hitTopWall();
  bool hitBottomWall();
  bool hitRightWall();

  // // SDL_Point: A data stucture that defines a two dimensional point.
  // // Data Fields: int x, int y
  // SDL_Point mWindowPosition; // Position of window
  // SDL_Point mWindowSize;     // Size of window
  // SDL_Point mMousePosition;  // Mouse position coordinates

  // Member data
  SDL_Window *mWindow;     // Window created by SDL2 Lib
  SDL_Renderer *mRenderer; // Renderer for 2D drawing
  Uint32 mTicksCount;      // Number of ticks since the start of the game
  bool mIsRunning;         // Flag for if game should continue to run

  // Pong specific data members
  int mPaddleDir;     // Direction of the paddle
  Vector2 mPaddlePos; // Position of the paddle
  Vector2 mBallPos;   // Position of the ball
  Vector2 mBallVel;   // Velocity of the ball
};