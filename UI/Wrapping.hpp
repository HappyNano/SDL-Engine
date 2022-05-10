#ifndef SDL_ENGINE_UI_WRAPPING_HPP
#define SDL_ENGINE_UI_WRAPPING_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "Texture.hpp"

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
    void wrapLeftTop(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent = 0);
    void wrapCenterTop(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent = 0);
    void wrapRightTop(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent = 0);
    void wrapLeftEquator(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent = 0);
    void wrapCenterEquator(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent = 0);
    void wrapRightEquator(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent = 0);
    void wrapLeftBottom(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent = 0);
    void wrapCenterBottom(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent = 0);
    void wrapRightBottom(const SDL_Rect& rect, std::vector< Texture >& in_rects, int indent = 0);
  }
}

#endif
