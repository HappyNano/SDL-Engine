#include "Engine.hpp"
#include "Logs.hpp"

#include <stdexcept>
#include <functional>

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

SDLEngine::Engine::Engine(handler_type handler):
  handler_{handler},
  thread_{},
  timer_{Timer::makeDefaultTimer()}
{}

SDLEngine::Engine::~Engine()
{}

void SDLEngine::Engine::start(int FPS)
{
  timer_->setFPS(FPS);
  thread_ = std::thread(std::bind(&Engine::loop, *this));
}

void SDLEngine::Engine::wait()
{
  if (thread_.joinable())
  {
    thread_.join();
  }
  else
  {
    logs << LogLevel::ERROR << LogTag{"Engine"} << "There is no any thread";
  }
}

int SDLEngine::Engine::getFPS() const
{
  return timer_->getCurrentFPS();
}

void SDLEngine::Engine::loop()
{
  int return_value = 0;
  timer_->startTimer();
  while (return_value == 0)
  {
    timer_->updateTimer();
    return_value = handler_(getWindow(), getRenderer(), *this);
  }
}

SDL_Window* SDLEngine::Engine::getWindow()
{
  return window;
}

SDL_Renderer* SDLEngine::Engine::getRenderer()
{
  return renderer;
}

int SDLEngine::Engine::SDLInit()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0 || TTF_Init() < 0)
  {
    print_sdlerror();
    logs << LogLevel::ERROR << LogTag{"SDL"} << "Bad initialization!";
    return 1;
  }
  logs << LogLevel::INFO << LogTag{"SDL"} << "Initialized.";
  return 0;
}

int SDLEngine::Engine::SDLQuit()
{
  closeWindow();
  SDL_Quit();
  TTF_Quit();
  logs << LogLevel::INFO << LogTag{"Engine"} << "Uninitialized.";
  return 0;
}

int SDLEngine::Engine::openWindow(const char* title, const int width, const int height)
{
  if (canBeStarted())
  {
    logs << LogLevel::ERROR << LogTag{"Engine"} << "Window and Renderer already exist!";
    return 1;
  }

  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!canBeStarted())
  {
    print_sdlerror();
    return -1;
  }
}

int SDLEngine::Engine::closeWindow()
{
  if (canBeStarted())
  {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
  }
  return 1;
}

bool SDLEngine::Engine::canBeStarted()
{
  return window && renderer;
}
