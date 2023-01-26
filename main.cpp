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

#include "Engine.hpp"

using SDLEngine::LogLevel;
using SDLEngine::logs;
using SDLEngine::LogTag;

namespace
{
  bool checkTextures(SDL_Renderer* renderer)
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
        logs << LogLevel::INFO << LogTag{"Textures"} << ("Loaded texture: " + asset_name.second);
      }
      else
      {
        logs << LogLevel::ERROR << LogTag{"Textures"} << ("Failed to load texture: " + asset_name.second);
        is_ok = false;
      }
    }

    return is_ok;
  }

  bool checkFonts()
  {
    bool is_ok = true;

    std::vector< std::pair< std::string, std::string > > fonts_names({
        {"default", "assets/ff.ttf"},
        //  {"test_texture", "assets/test.png"}
    });

    for (auto&& font_name: fonts_names)
    {
      if (SDLEngine::Assets::Instance().checkAndSaveFonts(font_name.first, font_name.second, 1))
      {
        logs << LogLevel::INFO << LogTag{"Fonts"} << ("Loaded font: " + font_name.second);
      }
      else
      {
        logs << LogLevel::ERROR << LogTag{"Fonts"} << ("Failed to load font: " + font_name.second);
        is_ok = false;
      }
    }

    return is_ok;
  }
}

constexpr int width = 300;
constexpr int height = 300;

int handler(SDL_Window*, SDL_Renderer* renderer, SDLEngine::Engine&)
{
  SDLEngine::UI::Texture cloud_texture{SDLEngine::Assets::Instance().getTextureByName(renderer, "cloud_small")};
  SDLEngine::Game::Sprite cloud(std::move(cloud_texture));
  cloud.move(50, 50);

  SDLEngine::UI::TextBox fps_textbox(u"233", SDL_Rect{0, 0, 0, 0}, {"default", 20, {0, 255, 0, 255}});

  SDLEngine::UI::Button test_button(u"нажми на меня", {50, 50, 100, 100}, {"default", 20, {255, 0, 0, 255}});
  SDLEngine::UI::Rectangle button_back(test_button.getRect(), {0, 0, 200, 200}, 10);
  test_button.setBackground(std::move(button_back));
  test_button.setFunction([]() {
    std::cout << "Pressed!\n";
  });

  bool stopped = false;
  // double x = 0;
  SDLEngine::TimerImpl timer;
  timer.setFPS(100);
  timer.startTimer();
  int fps_i = 0;
  while (!stopped)
  {
    timer.updateTimer();
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      test_button.handleEvent(event);
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

    cloud.render(renderer);

    test_button.render(renderer);
    fps_textbox.render(renderer);

    if (fps_i++ == 50)
    {
      std::wstring_convert< std::codecvt_utf8_utf16< char16_t >, char16_t > convert;
      fps_textbox.setText(convert.from_bytes(std::to_string(timer.getCurrentFPS())));
      fps_i = 0;
    }

    SDL_RenderPresent(renderer);
  }
  return 1;
}

int main()
{
  if (SDLEngine::Engine::SDLInit())
  {
    return 1;
  }
  SDLEngine::Engine::openWindow("SDL Engine", width, height);

  if (checkTextures(SDLEngine::Engine::getRenderer()) && checkFonts())
  {
    SDLEngine::Engine engine(handler);
    engine.start(100);
    engine.wait();
  }

  SDLEngine::Engine::SDLQuit();

  return 0;
}
