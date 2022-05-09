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
    Word(const std::wstring& str, const SDLEngine::UI::Font& font):
      text_(str),
      width_(font.getTextWidth(str)),
      height_(font.getTextHeight(str))
    {}

    const std::wstring& getWord() const
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
    std::wstring text_;
    int width_;
    int height_;
  };

  using words_t = std::vector< Word >;
  words_t splitTextToWords(std::wstring str, const SDLEngine::UI::Font& font)
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
  words_t splitWordByWidth(std::wstring str, const SDLEngine::UI::Font& font, int width)
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
  int getSumWidth(const words_t& words)
  {
    return std::accumulate(words.begin(), words.end(), 0, [](int result, const Word& word) {
      return result + word.getWidth();
    });
  }
}

SDLEngine::UI::STextBox::STextBox(const std::wstring& text, const SDL_Rect& rect, Font&& font):
  text_(text),
  wrapping_(SDLEngine::UI::Wrapping::none),
  font_(std::move(font)),
  text_surfaces_(),
  rect_(rect)
{}

SDLEngine::UI::STextBox::~STextBox()
{
  clearTextSurfaces();
}

void SDLEngine::UI::STextBox::setWidth(int width)
{
  rect_.w = width;
  doReCreateTextTextures();
}
void SDLEngine::UI::STextBox::setHeight(int heigth)
{
  rect_.h = heigth;
  doReCreateTextTextures();
}
void SDLEngine::UI::STextBox::setRect(const SDL_Rect& rect)
{
  rect_ = rect;
  doReCreateTextTextures();
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

void SDLEngine::UI::STextBox::clearTextSurfaces()
{
  text_surfaces_.clear();
}

void SDLEngine::UI::STextBox::addText(const std::wstring& text)
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

void SDLEngine::UI::STextBox::doReCreateTextTextures()
{
  reCreateTextTextures();
}

void SDLEngine::UI::STextBox::reCreateTextTextures()
{
  if (text_.empty())
  {
    return;
  }

  if (getHeight() && !getWidth())
  {
    addText(text_);
  }
  else
  {
    /* ===== Разбиение текста ===== */
    Word wh(L" ", font_);
    std::vector< Word > words = splitTextToWords(text_, font_);
    std::vector< Word > line_words;
    while (!words.empty())
    {
      Word next_word = words.front();
      if (getSumWidth(line_words) + next_word.getWidth() + wh.getWidth() > this->getWidth())
      {
        if (!line_words.empty())
        {
          addText(std::accumulate(line_words.begin(), line_words.end(), std::wstring(L""), [](std::wstring r, const Word& w) {
            return r + w.getWord();
          }));
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
            words.insert(insert_iter, new_word);
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
  }
}
