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

SDLEngine::Engine::Engine(handler_type handler, objects_type* objects):
  handler_{handler},
  handler_thread_{},
  graph_thread_{},
  objects_{objects},
  timer_{Timer::makeDefaultTimer()},
  running_{false}
{}

SDLEngine::Engine::~Engine()
{}

void SDLEngine::Engine::start(int FPS)
{
  running_ = true;
  timer_->setFPS(FPS);
  graph_thread_ = std::thread(std::bind(&SDLEngine::Engine::loopGraph, this));
  handler_thread_ = std::thread(handler_, Engine::getWindow(), Engine::getRenderer(), *this);
}

void SDLEngine::Engine::wait()
{
  if (handler_thread_.joinable())
  {
    handler_thread_.join();
  }
  running_ = false;
  if (graph_thread_.joinable())
  {
    graph_thread_.join();
  }
}

int SDLEngine::Engine::getFPS() const
{
  return timer_->getCurrentFPS();
}

typename SDLEngine::Engine::objects_type& SDLEngine::Engine::getObjects()
{
  return *objects_;
}

void SDLEngine::Engine::loopGraph()
{
  timer_->startTimer();
  while (running_)
  {
    timer_->updateTimer();
    SDL_RenderClear(Engine::getRenderer());
    for (auto&& obj: *objects_)
    {
      obj.lock()->render(Engine::getRenderer());
    }
    SDL_RenderPresent(Engine::getRenderer());
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

  return 0;
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
