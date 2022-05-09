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
      Font(const this_t&) = delete;
      Font(this_t&&) noexcept = default;
      ~Font();

      this_t& operator=(const this_t&) = delete;
      this_t& operator=(this_t&&) noexcept = default;

      SDL_Surface* renderSolidText(const std::string&) const;
      SDL_Surface* renderSolidText(const std::wstring&) const;

      int getTextWidth(const std::string&) const;
      int getTextHeight(const std::string&) const;
      SDL_Rect getTextRect(const std::string&) const;

      int getTextWidth(const std::wstring&) const;
      int getTextHeight(const std::wstring&) const;
      SDL_Rect getTextRect(const std::wstring&) const;

      size_t size_;
      SDL_Color color_;
      TTF_Font* font_;
    };
  }
}

#endif
