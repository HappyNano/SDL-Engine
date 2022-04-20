#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Geometry.hpp"

void print_sdlerror()
{
  std::cout << "ERROR [EngineSDL]: " << SDL_GetError() << std::endl;
}

constexpr int width = 200;
constexpr int height = 200;

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

  SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/cloud.png");
  if (!texture)
  {
    std::cerr << IMG_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  SDL_Rect texture_rect;
  SDL_QueryTexture(texture, NULL, NULL, &texture_rect.w, &texture_rect.h);

  SDL_Surface* surf = SDL_CreateRGBSurface(0, 100, 100, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
  Uint32 surf_color = SDL_MapRGBA(surf->format, 255, 10, 10, 255);
  SDLEngine::UI::draw_FillRoundedRectangle(surf, 0, 0, 100, 100, 20, surf_color);

  SDL_Texture* rounded_texture = SDL_CreateTextureFromSurface(renderer, surf);
  SDL_Rect rounded_rect{0, 0, 100, 100};
  SDL_FreeSurface(surf);

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
        break;
      }
    }

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
    SDL_RenderCopy(renderer, rounded_texture, NULL, &rounded_rect);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(rounded_texture);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
