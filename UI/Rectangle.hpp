#ifndef SDL_ENGINE_UI_RECTANGLE_HPP
#define SDL_ENGINE_UI_RECTANGLE_HPP

#include "UIElement.hpp"
#include "Surface.hpp"
#include "Texture.hpp"

namespace SDLEngine
{
  namespace UI
  {
    class Rectangle: UIElement
    {
    public:
      using this_t = Rectangle;

      Rectangle() = default;
      Rectangle(SDL_Rect, SDL_Color, int);
      Rectangle(this_t&&) noexcept;
      ~Rectangle() = default;

      this_t& operator=(this_t&&) noexcept;
      void swap(this_t&) noexcept;

      this_t& setWidth(int) override;
      this_t& setHeight(int) override;
      this_t& setX(int) override;
      this_t& setY(int) override;
      this_t& move(int, int) override;
      this_t& setRect(const SDL_Rect&) override;
      this_t& setColor(SDL_Color);
      this_t& setRadius(int);

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
