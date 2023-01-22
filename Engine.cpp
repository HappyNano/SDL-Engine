#include "Engine.hpp"
#include "Logs.hpp"

#include <stdexcept>

namespace
{
  using SDLEngine::LogLevel;
  using SDLEngine::logs;
  using SDLEngine::LogTag;
  void print_sdlerror()
  {
    logs << LogLevel::ERROR << LogTag{"Engine"} << SDL_GetError();
  }
}

SDLEngine::Engine::Engine(const char* title, const int width, const int height):
  window_(nullptr),
  renderer_(nullptr)
{
  window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!window_ || !renderer_)
  {
    print_sdlerror();
    throw std::logic_error("Bad initialization");
  }
}

SDLEngine::Engine::~Engine()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}

SDL_Window* SDLEngine::Engine::getWindow()
{
  return window_;
}

SDL_Renderer* SDLEngine::Engine::getRenderer()
{
  return renderer_;
}

void SDLEngine::Engine::start(handler_type handler)
{
  if (!canBeStarted())
  {
    throw std::logic_error("Error!");
  }
  handler(window_, renderer_);
}

int SDLEngine::Engine::SDLInit()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0 || TTF_Init() < 0)
  {
    print_sdlerror();
    logs << LogLevel::ERROR << LogTag{"SDL"} << "Bad initialization!";
    return 1;
  }
  return 0;
}

int SDLEngine::Engine::SDLQuit()
{
  SDL_Quit();
  TTF_Quit();
  return 0;
}

bool SDLEngine::Engine::canBeStarted() const
{
  return window_ && renderer_;
}
