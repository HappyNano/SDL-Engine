#ifndef SDL_ENGINE_ENGINE_HPP
#define SDL_ENGINE_ENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <functional>
#include <string>
#include <thread>
#include <vector>
#include <map>

#include "Timer.hpp"
#include "UI/Drawable.hpp"

namespace SDLEngine
{
  class SceneInterface
  {
  public:
    virtual ~SceneInterface() = default;

    virtual bool is_working() const = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void render() = 0;
    virtual void handleEvents() = 0;

    virtual size_t getHandlerTPS() const noexcept = 0;
    virtual size_t getGraphicsTPS() const noexcept = 0;

  protected:
    SceneInterface() = default;
  };

  class Engine
  {
  public:
    using scene_ptr = std::unique_ptr< SceneInterface >;
    using objects_type = std::vector< std::weak_ptr< UI::Drawable > >;

    Engine();
    ~Engine();

    void addScene(scene_ptr);
    size_t getCurrentSceneNum() const;
    void changeScene(size_t);

    void start();
    void stop();
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
    inline static SDL_Window* window{0};
    inline static SDL_Renderer* renderer{0};

    std::map< size_t, scene_ptr > scenes;
    size_t scene_id;

    std::thread handler_thread_;

    std::unique_ptr< Timer > render_timer_; // There can be your own timer
    std::unique_ptr< Timer > handler_timer_;

    void loopRender(size_t);
  };
}

#endif
