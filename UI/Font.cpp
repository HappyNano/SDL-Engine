#include "Font.hpp"
#include <iostream>
#include "SDLMethods.hpp"
#include "Assets.hpp"

SDLEngine::UI::Font::Font(TTF_Font* font, size_t size, SDL_Color color):
  size_(size),
  color_(color),
  font_(font)
{}

SDLEngine::UI::Font::Font(TTF_Font* font):
  Font(font, 14, {0, 0, 0, 255})
{}

// SDLEngine::UI::Font::Font(const std::string& font_name):
//   Font(Assets)
// {}

SDLEngine::UI::Font::~Font()
{
  if (font_)
  {
    TTF_CloseFont(font_);
  }
}

// void SDLEngine::UI::Font::swap(this_t& obj) noexcept
// {
//   std::swap(texture_, obj.texture_);
//   std::swap(rect_, obj.rect_);
// }

// void SDLEngine::UI::Font::render(SDL_Renderer* renderer)
// {
//   if (!texture_)
//   {
//     std::cerr << "ERROR [EngineSDL][Font]: Font is nullptr" << std::endl;
//     return;
//   }
//   SDL_RenderCopy(renderer, texture_, NULL, &rect_);
// }

SDL_Surface* SDLEngine::UI::Font::renderSolidText(const std::wstring& text)
{
  return TTF_RenderUNICODE_Solid(font_, reinterpret_cast< const Uint16* >(text.c_str()), color_);
}

int SDLEngine::UI::Font::getTextWidth(const std::wstring& text)
{
  int w = 0, h = 0;
  TTF_SizeUNICODE(this->font_, reinterpret_cast< const Uint16* >(text.c_str()), &w, &h);
  return w;
}
