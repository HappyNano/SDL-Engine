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
      virtual void setWidth(int) = 0;
      virtual void setHeight(int) = 0;
      virtual void setX(int) = 0;
      virtual void setY(int) = 0;
      virtual void move(int, int) = 0;
      virtual void setRect(const SDL_Rect&) = 0;

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
