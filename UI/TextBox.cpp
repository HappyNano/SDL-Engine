#include "TextBox.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <functional>
#include <algorithm>
#include <numeric>

#include "SDLMethods.hpp"
#include "Logs.hpp"

namespace
{
  struct Word
  {
    Word(const std::u16string& str, const SDLEngine::UI::Font& font):
      text_(str),
      width_(font.getTextWidth(str)),
      height_(font.getTextHeight(str))
    {}

    const std::u16string& getWord() const
    {
      return text_;
    }
    int getWidth() const
    {
      return width_;
    }
    int getHeight() const
    {
      return height_;
    }

  private:
    std::u16string text_;
    int width_;
    int height_;
  };

  using words_t = std::vector< Word >;
  words_t splitTextToWords(std::u16string str, const SDLEngine::UI::Font& font)
  {
    words_t words;
    size_t next_space = str.find_first_of(' ');
    while (next_space != str.npos)
    {
      words.emplace_back(str.substr(0, next_space), font);
      str.erase(0, next_space + 1);
      next_space = str.find_first_of(' ');
    }
    if (!str.empty())
    {
      words.emplace_back(str, font);
    }
    return words;
  }
  words_t splitWordByWidth(std::u16string str, const SDLEngine::UI::Font& font, int width)
  {
    words_t words;
    while (!str.empty())
    {
      size_t word_size = 0;
      for (; word_size < str.size(); ++word_size)
      {
        if (font.getTextWidth(str.substr(0, word_size)) > width)
        {
          --word_size;
          break;
        }
      }
      words.emplace_back(str.substr(0, word_size), font);
      str.erase(0, word_size);
    }
    return words;
  }
  std::u16string getSumText(const words_t& words)
  {
    return std::accumulate(words.begin(), words.end(), std::u16string(u""), [](std::u16string r, const Word& w) {
      return r + w.getWord();
    });
  }
  int getSumWidth(const words_t& words)
  {
    return std::accumulate(words.begin(), words.end(), 0, [](int result, const Word& word) {
      return result + word.getWidth();
    });
  }
}

SDLEngine::UI::TextBoxBase::TextBoxBase(const std::u16string& text, const SDL_Rect& rect, Font&& font):
  text_(text),
  font_(std::move(font)),
  text_surfaces_(),
  rect_(rect)
{
  doReCreateTextTextures();
}

SDLEngine::UI::TextBoxBase::~TextBoxBase()
{
  clearTextSurfaces();
}

void SDLEngine::UI::TextBoxBase::setWidth(int width)
{
  rect_.w = width;
  doReCreateTextTextures();
}
void SDLEngine::UI::TextBoxBase::setHeight(int heigth)
{
  rect_.h = heigth;
  doReCreateTextTextures();
}
void SDLEngine::UI::TextBoxBase::setX(int x)
{
  move(x - getX(), 0);
}
void SDLEngine::UI::TextBoxBase::setY(int y)
{
  move(0, y - getY());
}
void SDLEngine::UI::TextBoxBase::setRect(const SDL_Rect& rect)
{
  rect_ = rect;
  doReCreateTextTextures();
}
void SDLEngine::UI::TextBoxBase::setText(const std::u16string& text)
{
  text_ = text;
  doReCreateTextTextures();
}

int SDLEngine::UI::TextBoxBase::getWidth() const
{
  return getRect().w;
}
int SDLEngine::UI::TextBoxBase::getHeight() const
{
  return getRect().h;
}
int SDLEngine::UI::TextBoxBase::getX() const
{
  return getRect().x;
}
int SDLEngine::UI::TextBoxBase::getY() const
{
  return getRect().y;
}
const SDL_Rect& SDLEngine::UI::TextBoxBase::getRect() const
{
  return rect_;
}

void SDLEngine::UI::TextBoxBase::clearTextSurfaces()
{
  text_surfaces_.clear();
}

void SDLEngine::UI::TextBoxBase::addText(const std::u16string& text)
{
  SDL_Surface* textSurface = font_.renderSolidText(text);
  if (textSurface)
  {
    text_surfaces_.push_back(textSurface);
  }
  else
  {
    Logs::print("TextBox", "Failed to render text!", LogLevel::ERROR);
  }
}

void SDLEngine::UI::TextBoxBase::doReCreateTextTextures()
{
  clearTextSurfaces();
  reCreateTextSurfaces();
}

void SDLEngine::UI::TextBoxBase::reCreateTextSurfaces()
{
  clearTextSurfaces();
  if (text_.empty())
  {
    return;
  }

  if (!getWidth())
  {
    addText(text_);
  }
  else
  {
    /* ===== Разбиение текста ===== */
    Word wh(u" ", font_);
    std::vector< Word > words = splitTextToWords(text_, font_);
    std::vector< Word > line_words;
    while (!words.empty())
    {
      Word next_word = words.front();
      if (getSumWidth(line_words) + next_word.getWidth() + wh.getWidth() > this->getWidth())
      {
        if (!line_words.empty())
        {
          addText(getSumText(line_words));
          line_words.clear();
        }
        else
        {
          words.erase(words.begin());
          std::vector< Word > splitted_words = splitWordByWidth(next_word.getWord(), font_, this->getWidth());
          line_words.push_back(splitted_words.at(0));
          splitted_words.erase(splitted_words.begin());
          auto insert_iter = words.begin();
          for (auto&& new_word: splitted_words)
          {
            words.insert(insert_iter++, new_word);
          }
        }
      }
      else
      {
        words.erase(words.begin());
        line_words.push_back(next_word);
        line_words.push_back(wh);
      }
    }
    if (!line_words.empty())
    {
      addText(getSumText(line_words));
    }
  }
}

SDLEngine::UI::TextBox::TextBox(const std::u16string& text, const SDL_Rect& rect, Font&& font):
  TextBoxBase(text, rect, std::move(font)),
  padding_{5, 5, 5, 5},
  indent_(3),
  wrapping_(Wrapping::leftTop),
  text_textures_(),
  background_({{0, 0, 1, 1}, {0, 0, 0, 0}, 0})
{
  doReCreateTextTextures();
}

void SDLEngine::UI::TextBox::setRectangle(Rectangle&& rect)
{
  background_ = std::move(rect);
}
void SDLEngine::UI::TextBox::move(int offset_x, int offset_y)
{
  rect_ += {offset_x, offset_y};
  for (auto&& texture: text_textures_)
  {
    texture.move(offset_x, offset_y);
  }
}
void SDLEngine::UI::TextBox::handleEvent(const SDL_Event&)
{}

void SDLEngine::UI::TextBox::render(SDL_Renderer* renderer)
{
  if (text_textures_.empty() && !text_surfaces_.empty())
  {
    reCreateTextTextures(renderer);
  }
  background_.render(renderer);
  std::for_each(text_textures_.begin(), text_textures_.end(), std::bind(&Texture::render, std::placeholders::_1, renderer));
}

void SDLEngine::UI::TextBox::clearTextTextures()
{
  text_textures_.clear();
}

void SDLEngine::UI::TextBox::reCreateTextTextures(SDL_Renderer* renderer)
{
  clearTextTextures();
  auto builder = std::bind(&Surface::createTexture, std::placeholders::_1, renderer);
  std::transform(text_surfaces_.begin(), text_surfaces_.end(), std::back_inserter(text_textures_), builder);

  SDL_Rect rect = rect_;
  rect.h = std::accumulate(text_textures_.begin(), text_textures_.end(), 0, [&](int result, const Texture& texture) {
    return result + texture.rect_.h + indent_;
  });
  rect.h = rect.h - indent_ + padding_[0] + padding_[2]; // std::max(rect.h - indent_ + padding_[0] + padding_[2], height_);
  // rect.w = std::max(rect.w, (int)width_);

  SDL_Rect text_rect;
  text_rect.x = rect.x + padding_[3];
  text_rect.y = rect.y + padding_[0]; // Top Rigth Bottom Left
  text_rect.w = rect.w - padding_[1] - padding_[3];
  text_rect.h = rect.h - padding_[0] - padding_[2];

  if (this->text_textures_.size() == 0)
  {
    rect_.w = rect.w;
    rect_.h = rect.h;
    return;
  };

  switch (wrapping_)
  {
  case Wrapping::leftEquator:
    wrapLeftEquator(text_rect, text_textures_, indent_);
    break;
  case Wrapping::rightEquator:
    wrapRightEquator(text_rect, text_textures_, indent_);
    break;
  case Wrapping::centerTop:
    wrapCenterTop(text_rect, text_textures_, indent_);
    break;
  case Wrapping::centerBottom:
    wrapCenterBottom(text_rect, text_textures_, indent_);
    break;
  case Wrapping::leftTop:
    wrapLeftTop(text_rect, text_textures_, indent_);
    break;
  case Wrapping::leftBottom:
    wrapLeftBottom(text_rect, text_textures_, indent_);
    break;
  case Wrapping::rightTop:
    wrapRightTop(text_rect, text_textures_, indent_);
    break;
  case Wrapping::rightBottom:
    wrapRightBottom(text_rect, text_textures_, indent_);
    break;
  case Wrapping::centerEquator:
    wrapCenterEquator(text_rect, text_textures_, indent_);
    break;
  default:
    break;
  }
}

void SDLEngine::UI::TextBox::doReCreateTextTextures()
{
  reCreateTextSurfaces();
  clearTextTextures();
}
