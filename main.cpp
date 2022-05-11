#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <functional>

#include "UI/Sprite.hpp"
#include "UI/Geometry.hpp"
#include "UI/Texture.hpp"
#include "UI/Assets.hpp"
#include "UI/TextBox.hpp"
#include "UI/Rectangle.hpp"

#include "Logs.hpp"
#include "Timer.hpp"

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

constexpr int width = 1900;
constexpr int height = 1000;

void handler(SDL_Renderer* renderer)
{
  SDLEngine::Logs::Instance(std::cout, false);
  SDLEngine::UI::Texture cloud_texture{SDLEngine::Assets::Instance().getTextureByName(renderer, "cloud_small")};
  SDLEngine::UI::Sprite cloud(std::move(cloud_texture));

  SDLEngine::UI::Font f(TTF_OpenFont("assets/ff.ttf", 20), 10, {255, 0, 0, 255});
  SDLEngine::UI::TextBox tb(
      u"345 test1 приветабвгдеёжзийклмнопрстуфхцчшщъыьэюяfbcdefghijklmnopqrstuvwxyz test3 тест4 test5 тест6 test7 тест8 test9",
      SDL_Rect{0, 0, 200, 200}, std::move(f), renderer);
  SDL_Color rect_color = {0, 120, 120, 255};
  SDLEngine::UI::Rectangle rectt({10, 10, width - 20, height - 20}, rect_color, 40);

  bool stopped = false;
  double x = 0;
  SDLEngine::Timer timer;
  timer.setFPS(500);
  timer.startTimer();
  int fps_i = 0;
  while (!stopped)
  {
    timer.updateTimer();
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

    tb.render(renderer);
    rectt.render(renderer);
    x += 1e-2;
    rect_color.r = 128 * sin(x) + 128;
    rect_color.g = 128 * sin(x + 2.f * M_PI / 3.f) + 128;
    rect_color.b = 128 * sin(x + M_PI * 4.f / 3) + 128;
    rectt.setColor(rect_color);

    if (fps_i == 20)
    {
      // eng->recreateFPS(5, 5, 25, timer->getCurrentFPS());
      std::cout << "Current FPS: " << std::to_string(timer.getCurrentFPS()) << std::endl;
      fps_i = 0;
    }
    fps_i++;

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
