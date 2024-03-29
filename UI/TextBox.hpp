#ifndef SDL_ENGINE_UI_TEXTBOX_HPP
#define SDL_ENGINE_UI_TEXTBOX_HPP

#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include "Texture.hpp"
#include "Font.hpp"
#include "UIElement.hpp"
#include "Wrapping.hpp"
#include "Rectangle.hpp"

namespace SDLEngine
{
  namespace UI
  {
    class TextBoxBase: public UIElement
    {
    public:
      using this_t = TextBoxBase;

      TextBoxBase(const std::u16string&, const SDL_Rect&, Font&&);
      virtual ~TextBoxBase();

      this_t& setWidth(int) override;
      this_t& setHeight(int) override;
      virtual this_t& setX(int) override;
      virtual this_t& setY(int) override;
      virtual this_t& move(int, int) = 0;
      this_t& setRect(const SDL_Rect&) override;
      this_t& setText(const std::u16string&);

      int getWidth() const override;
      int getHeight() const override;
      int getX() const override;
      int getY() const override;
      const SDL_Rect& getRect() const override;

      virtual void handleEvent(const SDL_Event&) = 0;

      virtual void render(SDL_Renderer*) = 0;

    protected:
      std::u16string text_;

      Font font_;
      std::vector< Surface > text_surfaces_;

      SDL_Rect rect_;

      void clearTextSurfaces();
      void reCreateTextSurfaces();
      virtual void doReCreateTextTextures();
      void addText(const std::u16string&);
    };

    class TextBox: public TextBoxBase
    {
    public:
      using this_t = TextBox;

      TextBox(const std::u16string&, const SDL_Rect&, Font&&);
      virtual ~TextBox() = default;
  
      Rectangle& getBackground();

      this_t& move(int, int) override;
      void setBackground(Rectangle&&);
      void setWrapping(Wrapping);
      virtual void handleEvent(const SDL_Event&) override;

      virtual void render(SDL_Renderer*) override;

    private:
      int padding_[4];
      int indent_;
      Wrapping wrapping_;
      std::vector< Texture > text_textures_;
      Rectangle background_;

      void clearTextTextures();
      void reCreateTextTextures(SDL_Renderer*);
      void doReCreateTextTextures() override;
      void wrapTextures();
    };
  }
}

#endif
