#ifndef SDL_ENGINE_UI_TEXTBOX_HPP
#define SDL_ENGINE_UI_TEXTBOX_HPP

#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include "Texture.hpp"
#include "UIElements.hpp"

namespace SDLEngine
{
  namespace UI
  {
    enum class Wrapping
    {
      leftTop,       // Левый верхний угол
      centerTop,     // Сверху по центру
      rightTop,      // Правый верхний угол
      leftEquator,   // Слева посередине
      centerEquator, // По центру
      rightEquator,  // Справа посередине
      leftBottom,    // Левый нижний угол
      centerBottom,  // Снизу по центру
      rightBottom,   // Правый нижний угол
      none // Нет центровки никакой (Текст будет слева сверху и не будет подгоняться по размерам)
    };
    class TextBox: public UIElements
    {
    public:
      TextBox(const std::wstring&, const SDL_Rect&);
      ~TextBox();

      void setWidth(int) override;
      void setHeight(int) override;
      void setX(int) override;
      void setY(int) override;
      void move(int, int) override;
      void setRect(const SDL_Rect&) override;

      int getWidth() const override;
      int getHeight() const override;
      int getX() const override;
      int getY() const override;
      const SDL_Rect& getRect() const override;

      void handleEvent(const SDL_Event&) override;

      void render(SDL_Renderer*) override;

    private:
      std::wstring text_;

      Wrapping wrapping_;
      size_t font_size;
      TTF_Font* font_;
      SDL_Color font_color_;
      std::vector< Texture > text_textures_;

      SDL_Rect rect_;

      void clearTextTextures();
      void reRenderTextTextures();
    };
  }
}

#endif
