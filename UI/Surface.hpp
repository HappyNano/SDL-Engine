#ifndef SDL_ENGINE_UI_SURFACE_HPP
#define SDL_ENGINE_UI_SURFACE_HPP

#include <SDL2/SDL.h>

namespace SDLEngine
{
  namespace UI
  {
    struct Surface
    {
      using this_t = Surface;

      Surface() = delete;
      Surface(SDL_Surface*);
      Surface(const this_t&) = delete;
      Surface(this_t&&) noexcept;
      ~Surface();

      this_t& operator=(const this_t&) = delete;
      this_t& operator=(this_t&&) noexcept;

      void swap(this_t&) noexcept;

      SDL_Texture* createTexture(SDL_Renderer*);
      SDL_Rect getRect() const;

      SDL_Surface* surface_;
    };
  }
}

#endif
