#ifndef SDL_ENGINE_ENGINE_HPP
#define SDL_ENGINE_ENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <functional>
#include <string>

namespace SDLEngine
{
  class Engine
  {
  public:
    using handler_type = std::function< void(SDL_Window*, SDL_Renderer*) >;

    Engine() = delete;
    Engine(const char*, const int, const int);
    ~Engine();

    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();

    void start(handler_type);

    static int SDLInit();
    static int SDLQuit();

  private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;

    bool canBeStarted() const;
  };
}

#endif
