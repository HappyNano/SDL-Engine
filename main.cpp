#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "UI/Sprite.hpp"
#include "UI/Geometry.hpp"
#include "UI/Texture.hpp"

void print_sdlerror()
{
  std::cerr << "ERROR [EngineSDL]: " << SDL_GetError() << std::endl;
}

constexpr int width = 200;
constexpr int height = 200;

void handler(SDL_Renderer* renderer)
{
  SDLEngine::UI::Texture cloud_texture{IMG_LoadTexture(renderer, "assets/cloud.png")};
  std::cout << cloud_texture.texture_ << std::endl;
  SDLEngine::UI::Sprite cloud(std::move(cloud_texture));
  std::cout << cloud_texture.texture_ << std::endl;

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
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    print_sdlerror();
    std::cerr << "bad\n";
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
    return 1;
  }

  handler(renderer);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
