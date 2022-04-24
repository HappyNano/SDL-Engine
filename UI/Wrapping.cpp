#include "Wrapping.hpp"

const int ANY = 0;

void SDLEngine::UI::wrapLeftTop(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent)
{                 // O * *
  int y = rect.y; // * * *
  int x = rect.x; // * * *
  for (size_t i = 0; i < in_rects.size(); i++)
  {
    in_rects.at(i).rect_.x = x;
    in_rects.at(i).rect_.y = y;
    y += in_rects.at(i).rect_.h + indent;
  }
}
void SDLEngine::UI::wrapCenterTop(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent)
{                              // * O *
  int y = rect.y;              // * * *
  int x = rect.x + rect.w / 2; // * * *
  for (size_t i = 0; i < in_rects.size(); i++)
  {
    in_rects.at(i).rect_.x = x + in_rects.at(i).rect_.w / 2;
    in_rects.at(i).rect_.y = y;
    y += in_rects.at(i).rect_.h + indent;
  }
}
void SDLEngine::UI::wrapRightTop(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent)
{                          // * * O
  int y = rect.y;          // * * *
  int x = rect.x + rect.w; // * * *
  for (size_t i = 0; i < in_rects.size(); i++)
  {
    in_rects.at(i).rect_.x = x - in_rects.at(i).rect_.w;
    in_rects.at(i).rect_.y = y;
    y += in_rects.at(i).rect_.h + indent;
  }
}
void SDLEngine::UI::wrapLeftEquator(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent)
{                                                                                                // * * *
  int totalHeight = in_rects.size() * in_rects.at(ANY).rect_.h + (in_rects.size() - 1) * indent; // O * *
  int y = rect.y + (rect.h - totalHeight) / 2;                                                   // * * *
  int x = rect.x;
  for (size_t i = 0; i < in_rects.size(); i++)
  {
    in_rects.at(i).rect_.x = x;
    in_rects.at(i).rect_.y = y;
    y += in_rects.at(i).rect_.h + indent;
  }
}
void SDLEngine::UI::wrapCenterEquator(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent)
{                                                                                                // * * *
  int totalHeight = in_rects.size() * in_rects.at(ANY).rect_.h + (in_rects.size() - 1) * indent; // * O *
  int y = rect.y + (rect.h - totalHeight) / 2;                                                   // * * *
  int x = rect.x + rect.w / 2;
  for (size_t i = 0; i < in_rects.size(); i++)
  {
    in_rects.at(i).rect_.x = x - in_rects.at(i).rect_.w / 2;
    in_rects.at(i).rect_.y = y;
    y += in_rects.at(i).rect_.h + indent;
  }
}
void SDLEngine::UI::wrapRightEquator(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent)
{                                                                                                // * * *
  int totalHeight = in_rects.size() * in_rects.at(ANY).rect_.h + (in_rects.size() - 1) * indent; // * * O
  int y = rect.y + (rect.h - totalHeight) / 2;                                                   // * * *
  int x = rect.x + rect.w;
  for (size_t i = 0; i < in_rects.size(); i++)
  {
    in_rects.at(i).rect_.x = x - in_rects.at(i).rect_.w;
    in_rects.at(i).rect_.y = y;
    y += in_rects.at(i).rect_.h + indent;
  }
}
void SDLEngine::UI::wrapLeftBottom(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent)
{                                                                                                // * * *
  int totalHeight = in_rects.size() * in_rects.at(ANY).rect_.h + (in_rects.size() - 1) * indent; // * * *
  int y = rect.y + rect.h - totalHeight;                                                         // O * *
  int x = rect.x;
  for (size_t i = 0; i < in_rects.size(); i++)
  {
    in_rects.at(i).rect_.x = x;
    in_rects.at(i).rect_.y = y;
    y += in_rects.at(i).rect_.h + indent;
  }
}
void SDLEngine::UI::wrapCenterBottom(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent)
{                                                                                                // * * *
  int totalHeight = in_rects.size() * in_rects.at(ANY).rect_.h + (in_rects.size() - 1) * indent; // * * *
  int y = rect.y + rect.h - totalHeight;                                                         // * O *
  int x = rect.x + rect.w / 2;
  for (size_t i = 0; i < in_rects.size(); i++)
  {
    in_rects.at(i).rect_.x = x - in_rects.at(i).rect_.w / 2;
    in_rects.at(i).rect_.y = y;
    y += in_rects.at(i).rect_.h + indent;
  }
}
void SDLEngine::UI::wrapRightBottom(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent)
{                                                                                                // * * *
  int totalHeight = in_rects.size() * in_rects.at(ANY).rect_.h + (in_rects.size() - 1) * indent; // * * *
  int y = rect.y + rect.h - totalHeight;                                                         // * * O
  int x = rect.x + rect.w;
  for (size_t i = 0; i < in_rects.size(); i++)
  {
    in_rects.at(i).rect_.x = x - in_rects.at(i).rect_.w;
    in_rects.at(i).rect_.y = y;
    y += in_rects.at(i).rect_.h + indent;
  }
}
