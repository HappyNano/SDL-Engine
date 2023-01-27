#ifndef SDL_ENGINE_ENGINE_HPP
#define SDL_ENGINE_ENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <functional>
#include <string>
#include <thread>

#include "Timer.hpp"
#include "Drawable.hpp"

namespace SDLEngine
{
  class SceneInterface
  {
  public:
    virtual ~SceneInterface() = default;

    virtual void render() = 0;
    virtual void handleEvents() = 0;

  protected:
    SceneInterface() = default;
  };

  class Engine
  {
  public:
    using objects_type = std::vector< std::weak_ptr< UI::Drawable > >;
    using handler_type = std::function< int(SDL_Window*, SDL_Renderer*, Engine&) >;

    Engine() = delete;
    Engine(handler_type, objects_type*);
    ~Engine();

    void start(int);
    void wait();
    int getFPS() const;
    objects_type& getObjects();

    static SDL_Window* getWindow();
    static SDL_Renderer* getRenderer();

    static int SDLInit();
    static int SDLQuit();
    static int openWindow(const char*, const int, const int);
    static int closeWindow();

    static bool canBeStarted();

  private:
    inline static SDL_Window* window{0};
    inline static SDL_Renderer* renderer{0};

    handler_type handler_;
    std::thread handler_thread_;
    std::thread graph_thread_;
    objects_type* objects_;

    std::unique_ptr< Timer > timer_; // There can be your own timer

    bool running_;

    void loopGraph();
  };
}

#endif
