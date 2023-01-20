#ifndef SDL_ENGINE_UI_ELEMENT_HPP
#define SDL_ENGINE_UI_ELEMENT_HPP

#include <SDL2/SDL.h>

namespace SDLEngine
{
  namespace UI
  {
    class UIElement
    {
    public:
      using this_t = UIElement;

      virtual this_t& setWidth(int) = 0;
      virtual this_t& setHeight(int) = 0;
      virtual this_t& setX(int) = 0;
      virtual this_t& setY(int) = 0;
      virtual this_t& move(int, int) = 0;
      virtual this_t& setRect(const SDL_Rect&) = 0;

      virtual int getWidth() const = 0;
      virtual int getHeight() const = 0;
      virtual int getX() const = 0;
      virtual int getY() const = 0;
      virtual const SDL_Rect& getRect() const = 0;

      virtual void handleEvent(const SDL_Event&) = 0;

      virtual void render(SDL_Renderer*) = 0;

    protected:
      UIElement() = default;
      virtual ~UIElement() = default;
    };
  }
}

#endif
