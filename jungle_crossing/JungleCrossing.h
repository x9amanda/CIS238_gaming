#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <Actor.h>
#include <unordered_map>
#include <ctime>   // For random seed
#include <cstdlib> // For rand() and srand()
#include <cmath>   // For sqrt()

struct Vector2
{
    float x;
    float y;
};

struct Actor
{
    SDL_Texture *texture;
    Vector2 pos;
    Vector2 vel;
    SDL_Rect collider;
};

class JungleCrossing
{
public:
    JungleCrossing();
    bool Initialize();
    void RunLoop();
    void Shutdown();

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    SDL_Texture *LoadTexture(const std::string &fileName);
    bool CheckCollision(const Ac &posA, const Vector2 &posB, int widthA, int heightA, int widthB, int heightB);

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    TTF_Font *mFont;
    std::unordered_map<std::string, SDL_Texture *> mTextures;
    std::vector<Actor> mActors;
    Actor mRabbit;
    Actor mMonkey;
    Actor mCroc;
    Actor mSnake;
    Actor mPanther;
    std::vector<Vector2> mCarrotPositions;
    int mScore;
    Uint32 mTicksCount;
    bool mIsRunning; // Flag for if game should continue to run
};