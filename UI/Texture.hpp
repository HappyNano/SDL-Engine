#ifndef SDL_ENGINE_UI_TEXTURE_HPP
#define SDL_ENGINE_UI_TEXTURE_HPP

#include <SDL2/SDL.h>
#include "Surface.hpp"

namespace SDLEngine
{
  namespace UI
  {
    struct Texture
    {
      using this_t = Texture;

      Texture();
      Texture(SDL_Texture*, const SDL_Rect&);
      Texture(SDL_Texture*);
      Texture(SDL_Renderer*, SDL_Surface*);
      Texture(SDL_Renderer*, Surface&&);
      Texture(const this_t&) = delete;
      Texture(this_t&&) noexcept;
      ~Texture();

      this_t& operator=(const this_t&) = delete;
      this_t& operator=(this_t&&) noexcept;

      void swap(this_t&) noexcept;
      void move(int, int);
      void render(SDL_Renderer*);

      bool valid() const;

      SDL_Texture* texture_;
      SDL_Rect rect_;
    };
  }
}

#endif
