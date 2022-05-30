#ifndef SDL_ENGINE_UI_SPRITE_HPP
#define SDL_ENGINE_UI_SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.hpp"

namespace SDLEngine
{
  namespace Game
  {
    class Sprite
    {
    public:
      using this_t = Sprite;

      Sprite() = delete;
      Sprite(UI::Texture&&);
      ~Sprite() = default;

      void render(SDL_Renderer*);

      void scale(double);
      void move(double, double);

      bool checkCollide(const SDL_Rect&) const;
      bool checkCollide(const this_t&) const;

      SDL_Rect getCollideRect() const;

    private:
      UI::Texture texture_;
      SDL_Rect collide_rect_;

      double scale_;
      double x_, y_;

      void correctCoordinates();
    };
  }
}

#endif