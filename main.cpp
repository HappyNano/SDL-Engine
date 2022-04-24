#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <vector>
#include <string>
#include <functional>

#include "UI/Sprite.hpp"
#include "UI/Geometry.hpp"
#include "UI/Texture.hpp"
#include "UI/Assets.hpp"

#include "Logs.hpp"

void print_sdlerror()
{
  SDLEngine::Logs::print("EngineSDL", SDL_GetError(), SDLEngine::LogLevel::ERROR);
}

namespace
{
  bool checkAssets(SDL_Renderer* renderer)
  {
    bool is_ok = true;

    std::vector< std::pair< std::string, std::string > > assets_names({
        {"cloud_small", "assets/cloud.png"},
        {"house_sunset", "assets/dom_z.png"},
        {"house_common", "assets/dom.png"},
        {"background_sunset", "assets/Zakat.png"},
        //  {"test_texture", "assets/test.png"}
    });

    for (auto&& asset_name: assets_names)
    {
      if (SDLEngine::Assets::Instance().checkAndSaveTextures(renderer, asset_name.first, asset_name.second))
      {
        SDLEngine::Logs::print("Textures", "Loaded texture: " + asset_name.second, SDLEngine::LogLevel::INFO);
      }
      else
      {
        SDLEngine::Logs::print("Textures", "Failed to load texture: " + asset_name.second, SDLEngine::LogLevel::ERROR);
        is_ok = false;
      }
    }

    return is_ok;
  }
}

constexpr int width = 200;
constexpr int height = 200;

void handler(SDL_Renderer* renderer)
{
  SDLEngine::Logs::Instance(std::cout, false);
  SDLEngine::UI::Texture cloud_texture{SDLEngine::Assets::Instance().getTextureByName(renderer, "cloud_small")};
  SDLEngine::UI::Sprite cloud(std::move(cloud_texture));

  bool stopped = false;
  while (!stopped)
  {
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        stopped = true;
        break;
      case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
          stopped = true;
        }
        else if (event.key.keysym.sym == SDLK_d)
        {
          cloud.move(2, 2);
        }
        break;
      }
    }

    SDL_RenderClear(renderer);

    // SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
    cloud.render(renderer);
    // SDL_RenderCopy(renderer, rounded_texture, NULL, &rounded_rect);

    SDL_RenderPresent(renderer);
  }
}

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

  window = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
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

  if (checkAssets(renderer))
  {
    handler(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  TTF_Quit();

  return 0;
}
