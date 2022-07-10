#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <locale>
#include <codecvt>
#include <vector>
#include <string>
#include <cmath>
#include <functional>

#include "Game/Sprite.hpp"
#include "UI/Geometry.hpp"
#include "UI/Texture.hpp"
#include "UI/Assets.hpp"
#include "UI/TextBox.hpp"
#include "UI/Button.hpp"
#include "UI/Rectangle.hpp"

#include "Logs.hpp"
#include "Timer.hpp"

#include "SnakeGame.hpp"

void print_sdlerror()
{
  SDLEngine::Logs::print("EngineSDL", SDL_GetError(), SDLEngine::LogLevel::ERROR);
}

constexpr int width = 300;
constexpr int height = 300;

int main()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0 || TTF_Init() < 0)
  {
    print_sdlerror();
    SDLEngine::Logs::print("SDL", "Bad initialization!", SDLEngine::LogLevel::ERROR);
    return 1;
  }

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (window == nullptr || renderer == nullptr)
  {
    print_sdlerror();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    return 1;
  }

  std::srand(std::time(0));
  Game::SnakeGame game(window, renderer, 20);
  game.start();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  TTF_Quit();

  return 0;
}
