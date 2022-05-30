#ifndef SDL_ENGINE_UI_BUTTON_HPP
#define SDL_ENGINE_UI_BUTTON_HPP

#include "TextBox.hpp"
#include <functional>

namespace SDLEngine
{
  namespace UI
  {
    class Button: public TextBox
    {
    public:
      using func_type = std::function< void(void) >;

      Button(const std::u16string&, const SDL_Rect&, Font&&);
      virtual ~Button() = default;

      void setFunction(func_type);
      func_type& getFunction() const;

      virtual void handleEvent(const SDL_Event&) override;

      virtual void render(SDL_Renderer*) override;

    private:
      func_type function_;
    };
  }
}

#endif
