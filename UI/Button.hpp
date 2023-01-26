#ifndef SDL_ENGINE_UI_BUTTON_HPP
#define SDL_ENGINE_UI_BUTTON_HPP

#include "TextBox.hpp"
#include <functional>

namespace SDLEngine
{
  namespace UI
  {
    class Button: virtual public TextBox
    {
    public:
      using func_type = std::function< void(void) >;

      Button(const std::u16string&, const SDL_Rect&, Font&&);
      virtual ~Button() = default;

      void setFunction(func_type);
      func_type getFunction() const;

      virtual void handleEvent(const SDL_Event&) override;

    private:
      SDL_Color normal_color_;
      SDL_Color hovered_color_;
      SDL_Color pressed_color_;
      bool is_hovered_;
      bool is_pressed_;

      func_type function_;
    };
  }
}

#endif
