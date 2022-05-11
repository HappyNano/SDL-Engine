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
      Font(TTF_Font*, SDL_Color);
      Font(const std::string&, int, SDL_Color);
      Font(TTF_Font*);
      Font(const std::string&, int);
      Font(const this_t&) = delete;
      Font(this_t&&) noexcept;
      ~Font();

      this_t& operator=(const this_t&) = delete;
      this_t& operator=(this_t&&) noexcept;

      void swap(this_t&) noexcept;

      SDL_Surface* renderSolidText(const std::string&) const;
      SDL_Surface* renderSolidText(const std::u16string&) const;

      int getTextWidth(const std::string&) const;
      int getTextHeight(const std::string&) const;
      SDL_Rect getTextRect(const std::string&) const;

      int getTextWidth(const std::u16string&) const;
      int getTextHeight(const std::u16string&) const;
      SDL_Rect getTextRect(const std::u16string&) const;

      SDL_Color color_;
      TTF_Font* font_;
    };
  }
}

#endif
