#ifndef SDL_ENGINE_UI_TEXTBOX_HPP
#define SDL_ENGINE_UI_TEXTBOX_HPP

#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include "Texture.hpp"
#include "Font.hpp"
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
    class STextBox: public UIElements
    {

    public:
      STextBox(const std::wstring&, const SDL_Rect&, Font&&);
      virtual ~STextBox();

      void setWidth(int) override;
      void setHeight(int) override;
      virtual void setX(int) = 0;
      virtual void setY(int) = 0;
      virtual void move(int, int) = 0;
      void setRect(const SDL_Rect&) override;

      int getWidth() const override;
      int getHeight() const override;
      int getX() const override;
      int getY() const override;
      const SDL_Rect& getRect() const override;

      virtual void handleEvent(const SDL_Event&) = 0;

      virtual void render(SDL_Renderer*) = 0;

    protected:
      std::wstring text_;

      Wrapping wrapping_;
      Font font_;
      std::vector< Surface > text_surfaces_;

      SDL_Rect rect_;

      void clearTextSurfaces();
      void reCreateTextTextures();
      virtual void doReCreateTextTextures();
      void addText(const std::wstring&);
    };
    // class TextBox: public STextBox
    // {

    // };
  }
}

#endif
