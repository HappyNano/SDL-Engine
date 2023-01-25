#ifndef SDL_ENGINE_ENGINE_HPP
#define SDL_ENGINE_ENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <functional>
#include <string>
#include <thread>

#include "Timer.hpp"

namespace SDLEngine
{
  class Engine
  {
  public:
    using handler_type = std::function< int(SDL_Window*, SDL_Renderer*, Engine&) >;

    Engine() = delete;
    Engine(handler_type);
    ~Engine();

    void start(int);
    void wait();
    int getFPS() const;

    static SDL_Window* getWindow();
    static SDL_Renderer* getRenderer();

    static int SDLInit();
    static int SDLQuit();
    static int openWindow(const char*, const int, const int);
    static int closeWindow();

    static bool canBeStarted();

  private:
    static SDL_Window* window;
    static SDL_Renderer* renderer;

    handler_type handler_;
    std::thread thread_;

    std::unique_ptr< Timer > timer_; // There can be your own timer

    void loop();
  };
}

#endif
