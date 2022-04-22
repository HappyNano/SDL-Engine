#include "TextBox.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <algorithm>

SDLEngine::UI::TextBox::TextBox(const std::wstring& text, const SDL_Rect& rect):
  text_(text),
  rect_(rect)
{}

SDLEngine::UI::TextBox::~TextBox()
{
  clearTextTextures();
  TTF_CloseFont(font_);
}

void SDLEngine::UI::TextBox::setWidth(int width)
{
  rect_.w = width;
}
void SDLEngine::UI::TextBox::setHeight(int heigth)
{
  rect_.h = heigth;
}
void SDLEngine::UI::TextBox::setX(int x)
{
  rect_.x = x;
}
void SDLEngine::UI::TextBox::setY(int y)
{
  rect_.y = y;
}
void SDLEngine::UI::TextBox::setRect(const SDL_Rect& rect)
{
  rect_ = rect;
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
{}

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
