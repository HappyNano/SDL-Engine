#include "TextBox.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <algorithm>

#include "SDLMethods.hpp"

namespace
{
  // int get_textWidth(const std::wstring& text, TTF_Font* font)
  // {
  //   int w = 0, h = 0;
  //   TTF_SizeUNICODE(font, reinterpret_cast< const Uint16* >(text.c_str()), &w, &h);
  //   return w;
  // }
}

SDLEngine::UI::TextBox::TextBox():
  text_(L""),
  wrapping_(SDLEngine::UI::Wrapping::none),
  font_size_(14),
  font_(nullptr),
  font_color_({0, 0, 0, 255}),
  text_textures_(),
  rect_()
{}

SDLEngine::UI::TextBox::TextBox(const std::wstring& text, const SDL_Rect& rect):
  TextBox()
{
  text_ = text;
  rect_ = rect;
}

SDLEngine::UI::TextBox::~TextBox()
{
  clearTextTextures();
  TTF_CloseFont(font_);
}

void SDLEngine::UI::TextBox::setWidth(int width)
{
  rect_.w = width;
  reRenderTextTextures();
}
void SDLEngine::UI::TextBox::setHeight(int heigth)
{
  rect_.h = heigth;
  reRenderTextTextures();
}
void SDLEngine::UI::TextBox::setX(int x)
{
  move(x - rect_.x, 0);
}
void SDLEngine::UI::TextBox::setY(int y)
{
  move(0, y - rect_.y);
}
void SDLEngine::UI::TextBox::move(int offset_x, int offset_y)
{
  for (auto&& texture: text_textures_)
  {
    texture.move(offset_x, offset_y);
  }
  rect_ += {offset_x, offset_y};
}
void SDLEngine::UI::TextBox::setRect(const SDL_Rect& rect)
{
  rect_ = rect;
  reRenderTextTextures();
}

int SDLEngine::UI::TextBox::getWidth() const
{
  return rect_.w;
}
int SDLEngine::UI::TextBox::getHeight() const
{
  return rect_.h;
}
int SDLEngine::UI::TextBox::getX() const
{
  return rect_.x;
}
int SDLEngine::UI::TextBox::getY() const
{
  return rect_.y;
}
const SDL_Rect& SDLEngine::UI::TextBox::getRect() const
{
  return rect_;
}

void SDLEngine::UI::TextBox::handleEvent(const SDL_Event&)
{
  // Nothing...
}

void SDLEngine::UI::TextBox::render(SDL_Renderer* renderer)
{
  for (auto&& texture: text_textures_)
  {
    texture.render(renderer);
  }
}

void SDLEngine::UI::TextBox::clearTextTextures()
{
  text_textures_.clear();
}

void SDLEngine::UI::TextBox::reRenderTextTextures()
{}
