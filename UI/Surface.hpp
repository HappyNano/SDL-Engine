#ifndef SDL_ENGINE_UI_SURFACE_HPP
#define SDL_ENGINE_UI_SURFACE_HPP

#include <SDL2/SDL.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00
#define AMASK 0x000000ff
#else
#define RMASK 0x000000ff
#define GMASK 0x0000ff00
#define BMASK 0x00ff0000
#define AMASK 0xff000000
#endif

namespace SDLEngine
{
  namespace UI
  {
    struct Surface
    {
      using this_t = Surface;

      Surface();
      Surface(SDL_Surface*);
      Surface(const this_t&) = delete;
      Surface(this_t&&) noexcept;
      ~Surface();

      this_t& operator=(const this_t&) = delete;
      this_t& operator=(this_t&&) noexcept;

      void swap(this_t&) noexcept;

      SDL_Texture* createTexture(SDL_Renderer*);
      SDL_Rect getRect() const;

      bool valid() const;

      SDL_Surface* surface_;
    };
  }
}

#endif
