#ifndef SDL_ENGINE_UI_RECTANGLE_HPP
#define SDL_ENGINE_UI_RECTANGLE_HPP

#include "UIElements.hpp"
#include "Surface.hpp"
#include "Texture.hpp"

namespace SDLEngine
{
  namespace UI
  {
    class Rectangle: UIElements
    {
    public:
      using this_t = Rectangle;

      Rectangle() = default;
      Rectangle(SDL_Rect, SDL_Color, int);
      Rectangle(this_t&&) noexcept;
      ~Rectangle() = default;

      this_t& operator=(this_t&&) noexcept;
      void swap(this_t&) noexcept;

      void setWidth(int) override;
      void setHeight(int) override;
      void setX(int) override;
      void setY(int) override;
      void move(int, int) override;
      void setRect(const SDL_Rect&) override;
      void setColor(SDL_Color);
      void setRadius(int);

      int getWidth() const override;
      int getHeight() const override;
      int getX() const override;
      int getY() const override;
      const SDL_Rect& getRect() const override;

      void handleEvent(const SDL_Event&) override;

      void render(SDL_Renderer*) override;

    private:
      SDL_Color color_;
      int round_radius_;
      SDL_Rect rect_;
      Surface surface_;
      Texture texture_;

      void reRender();
    };
  }
}

#endif
