#ifndef SDL_ENGINE_UI_TEXTURE_HPP
#define SDL_ENGINE_UI_TEXTURE_HPP

#include <SDL2/SDL.h>

namespace SDLEngine
{
  namespace UI
  {
    struct Texture
    {
      using this_t = Texture;

      Texture() = delete;
      Texture(SDL_Texture*, const SDL_Rect&);
      Texture(SDL_Texture*);
      Texture(const this_t&) = delete;
      Texture(this_t&&) noexcept;
      ~Texture();

      this_t& operator=(const this_t&) = delete;
      this_t& operator=(this_t&&) noexcept;

      void swap(this_t&) noexcept;
      void render(SDL_Renderer*);

      SDL_Texture* texture_;
      SDL_Rect rect_;
    };
  }
}

#endif