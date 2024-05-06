#pragma once

#include <string>
#include <SDL2/SDL.h>

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& fileName);