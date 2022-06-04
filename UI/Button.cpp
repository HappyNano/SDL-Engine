#include "Button.hpp"

SDLEngine::UI::Button::Button(const std::u16string& text, const SDL_Rect& rect, Font&& font):
  TextBox(text, rect, std::move(font)),
  normal_color_{0, 0, 255, 200},
  hovered_color_{100, 100, 200, 255},
  pressed_color_{0, 100, 0, 255},
  is_hovered_{false},
  is_pressed_{false},
  function_()
{}

void SDLEngine::UI::Button::setFunction(func_type func)
{
  function_ = func;
}
typename SDLEngine::UI::Button::func_type SDLEngine::UI::Button::getFunction() const
{
  return function_;
}

void SDLEngine::UI::Button::handleEvent(const SDL_Event& event)
{
  switch (event.type)
  {
  case SDL_MOUSEMOTION: {
    SDL_Rect motion_rect{event.motion.x, event.motion.y, 1, 1};
    is_hovered_ = SDL_IntersectRect(std::addressof(motion_rect), std::addressof(rect_), std::addressof(motion_rect));
  }
  break;
  case SDL_MOUSEBUTTONDOWN: {
    SDL_Rect button_rect{event.button.x, event.button.y, 1, 1};
    if (SDL_IntersectRect(std::addressof(button_rect), std::addressof(rect_), std::addressof(button_rect)))
    {
      is_pressed_ = true;
    }
  }
  break;
  case SDL_MOUSEBUTTONUP: {
    is_pressed_ = false;
    SDL_Rect button_rect{event.button.x, event.button.y, 1, 1};
    if (SDL_IntersectRect(std::addressof(button_rect), std::addressof(rect_), std::addressof(button_rect)))
    {
      if (function_)
      {
        function_();
      }
    }
    break;
  }
  }

  if (is_pressed_)
  {
    getBackground().setColor(pressed_color_);
  }
  else if (is_hovered_)
    getBackground().setColor(hovered_color_);
  else
  {
    getBackground().setColor(normal_color_);
  }
}