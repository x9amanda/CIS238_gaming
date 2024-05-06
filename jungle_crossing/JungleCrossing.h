#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class JungleCrossing {
public:
    JungleCrossing();
    bool Initialize();
    void RunLoop();
    void Shutdown();

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    SDL_Texture* LoadTexture(const std::string& fileName);
    bool CheckCollision(const Vector2& posA, const Vector2& posB, int widthA, int heightA, int widthB, int heightB);

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;
    std::vector<Actor> mActors;
    Actor mRabbit;
    std::vector<Vector2> mCarrotPositions;
    int mScore;
    Uint32 mTicksCount;
};