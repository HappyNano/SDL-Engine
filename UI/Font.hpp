#ifndef SDL_ENGINE_UI_FONT_HPP
#define SDL_ENGINE_UI_FONT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace SDLEngine
{
  namespace UI
  {
    struct Font
    {
      using this_t = Font;

      Font() = delete;
      Font(TTF_Font*, size_t, SDL_Color);
      Font(TTF_Font*);
      // Font(const std::string&);
      Font(const this_t&) = delete;
      Font(this_t&&) noexcept = default;
      ~Font();

      this_t& operator=(const this_t&) = delete;
      this_t& operator=(this_t&&) noexcept = default;

      // void swap(this_t&) noexcept;
      SDL_Surface* renderSolidText(const std::wstring&);

      int getTextWidth(const std::wstring&);

      size_t size_;
      SDL_Color color_;
      TTF_Font* font_;
    };
  }
}

#endif
