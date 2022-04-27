#include "TextBox.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <algorithm>

#include "SDLMethods.hpp"

SDLEngine::UI::STextBox::STextBox(const std::wstring& text, const SDL_Rect& rect, Font&& font):
  text_(text),
  wrapping_(SDLEngine::UI::Wrapping::none),
  font_(std::move(font)),
  text_textures_(),
  rect_(rect)
{}

SDLEngine::UI::STextBox::~STextBox()
{
  clearTextTextures();
}

void SDLEngine::UI::STextBox::setWidth(int width)
{
  rect_.w = width;
  reRenderTextTextures();
}
void SDLEngine::UI::STextBox::setHeight(int heigth)
{
  rect_.h = heigth;
  reRenderTextTextures();
}
void SDLEngine::UI::STextBox::setX(int x)
{
  move(x - rect_.x, 0);
}
void SDLEngine::UI::STextBox::setY(int y)
{
  move(0, y - rect_.y);
}
void SDLEngine::UI::STextBox::move(int offset_x, int offset_y)
{
  for (auto&& texture: text_textures_)
  {
    texture.move(offset_x, offset_y);
  }
  rect_ += {offset_x, offset_y};
}
void SDLEngine::UI::STextBox::setRect(const SDL_Rect& rect)
{
  rect_ = rect;
  reRenderTextTextures();
}

int SDLEngine::UI::STextBox::getWidth() const
{
  return rect_.w;
}
int SDLEngine::UI::STextBox::getHeight() const
{
  return rect_.h;
}
int SDLEngine::UI::STextBox::getX() const
{
  return rect_.x;
}
int SDLEngine::UI::STextBox::getY() const
{
  return rect_.y;
}
const SDL_Rect& SDLEngine::UI::STextBox::getRect() const
{
  return rect_;
}

void SDLEngine::UI::STextBox::handleEvent(const SDL_Event&)
{
  // Nothing...
}

void SDLEngine::UI::STextBox::render(SDL_Renderer* renderer)
{
  for (auto&& texture: text_textures_)
  {
    texture.render(renderer);
  }
}

void SDLEngine::UI::STextBox::clearTextTextures()
{
  text_textures_.clear();
}

void SDLEngine::UI::STextBox::addText(const std::wstring& text)
{
  SDL_Surface* textSurface = font_.renderSolidText(text);
  if (textSurface)
  {
    textures_.push_back({renderer, textSurface});
    SDL_FreeSurface(textSurface);
  }
}

void SDLEngine::UI::STextBox::reCreateTextTextures()
{
  if (text_.empty() || !width_)
    return;

  if (height_ && !width_)
  {
    SDL_Surface* textSurface = font_.renderSolidText(text_);
    if (textSurface == nullptr)
    {
      printf("textSurface = nullptr!\n");
      return;
    }
    // GameEngine::DrawRectangle(textSurface, 0, 0, textSurface->w, textSurface->h,
    // SDL_MapRGBA(textSurface->format, 255, 225, 255, 255));
    this->text_textures_.push_back(SDL_CreateTextureFromSurface(renderer_, textSurface));
    this->text_rects_.push_back(new SDL_Rect({0, 0, textSurface->w, textSurface->h}));
    SDL_FreeSurface(textSurface);
  }
  else
  {
    /* ===== Разбиение текста ===== */

    int max_width = rect_.w - padding_[1] - padding_[3];

    int lastBreaker = -1;
    while (lastBreaker < (int)text_.size())
    {
      size_t nextBreaker = text_.find_first_of('\n', lastBreaker + 1);
      nextBreaker = nextBreaker == text_.npos ? text_.size() : nextBreaker;

      std::wstring text_line = L"";
      size_t lastSpace = lastBreaker + 1;
      while (lastSpace < nextBreaker)
      {
        size_t nextSpace = text_.find_first_of(' ', lastSpace + 1);
        nextSpace = nextSpace == text_.npos ? text_.size() : nextSpace;
        nextSpace = nextSpace > nextBreaker ? nextBreaker : nextSpace;

        std::wstring word = text_.substr(lastSpace, nextSpace - lastSpace);

        if (get_textWidth(word, font_) > max_width)
        {
          addText(text_line.c_str(), text_textures_, text_rects_, font_, font_color_, renderer_);
          text_line = L"";
          size_t word_size = 0;
          for (word_size = 1; word_size < word.size() && get_textWidth(word.substr(0, word_size), font_) < max_width; word_size++)
            ;
          word_size = std::max(word_size - 1, 1ull);
          addText(word.substr(0, word_size).c_str(), text_textures_, text_rects_, font_, font_color_, renderer_);
          lastSpace += word_size;
          continue;
        }
        if (get_textWidth(text_line + word, font_) > max_width)
        {
          addText(text_line.c_str(), text_textures_, text_rects_, font_, font_color_, renderer_);
          text_line = L"";
          continue;
        }
        else
        {
          text_line += word;
        }
        lastSpace = nextSpace;
      }
      addText(text_line.c_str(), text_textures_, text_rects_, font_, font_color_, renderer_);
      lastBreaker = nextBreaker;
    }
  }
}
