#ifndef SDL_ENGINE_UI_SPRITE_HPP
#define SDL_ENGINE_UI_SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace SDLEngine
{
  namespace UI
  {
    class Sprite
    {
    public:
      using this_t = Sprite;

      Sprite() = delete;
      Sprite(SDL_Rect);
      Sprite(const this_t&);
      Sprite(this_t&&) noexcept;
      ~Sprite();

      this_t& operator=(const this_t&);
      this_t& operator=(this_t&&) noexcept;
      void swap(this_t&) noexcept;

      void scale(double);
      void offset(double, double);

      bool checkCollide(SDL_Rect) const;
      bool checkCollide(const this_t&) const;

      SDL_Rect getCollideRect() const;

      void render(SDL_Renderer*);

    private:
      SDL_Texture* texture_;
      SDL_Rect texture_rect_;
      SDL_Rect collide_rect_;

      double scale_;
      double x_, y_;
    };
  }
}

#endif