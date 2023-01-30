#include "Engine.hpp"
#include "Logs.hpp"

#include <stdexcept>
#include <functional>

namespace
{
  using SDLEngine::LogLevel;
  using SDLEngine::logs;
  using SDLEngine::LogTag;
  using scene_ptr = typename SDLEngine::Engine::scene_ptr;
  using SDLEngine::Timer;
  void print_sdlerror()
  {
    logs << LogLevel::ERROR << LogTag{"Engine"} << SDL_GetError();
  }
  void looping(std::unique_ptr< Timer >& timer, std::map< size_t, scene_ptr >& scenes, size_t id)
  {
    timer->startTimer();
    while (scenes.at(id)->is_working())
    {
      timer->updateTimer();
      scenes.at(id)->render();
    }
  }
}

SDLEngine::Engine::Engine():
  scenes{},
  scene_id{0},
  handler_thread_{},
  render_timer_{Timer::makeDefaultTimer()},
  handler_timer_{Timer::makeDefaultTimer()}
{}

SDLEngine::Engine::~Engine()
{}

void SDLEngine::Engine::addScene(scene_ptr scene)
{
  scenes.insert({scenes.size(), std::move(scene)});
}

size_t SDLEngine::Engine::getCurrentSceneNum() const
{
  return scene_id;
}

void SDLEngine::Engine::changeScene(size_t new_id)
{
  auto&& current_scene = scenes.at(scene_id);
  current_scene->pause();
  handler_thread_.detach();

  scene_id = new_id;
  start();
}

void SDLEngine::Engine::start()
{
  auto&& current_scene = scenes.at(scene_id);
  render_timer_->setFPS(current_scene->getGraphicsTPS());
  handler_timer_->setFPS(current_scene->getHandlerTPS());
  current_scene->resume();
  handler_thread_ = std::thread(std::bind(looping, std::ref(handler_timer_), std::ref(scenes), scene_id));
  loopRender(scene_id);
}

void SDLEngine::Engine::stop()
{
  auto&& current_scene = scenes.at(scene_id);
  current_scene->pause();
  handler_thread_.detach();
}

void SDLEngine::Engine::wait()
{
  if (handler_thread_.joinable())
  {
    handler_thread_.join();
  }
}

int SDLEngine::Engine::getFPS() const
{
  return render_timer_->getCurrentFPS();
}

void SDLEngine::Engine::loopRender(size_t id)
{
  render_timer_->startTimer();
  while (scenes.at(id)->is_working())
  {
    render_timer_->updateTimer();
    scenes.at(scene_id)->render();
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
