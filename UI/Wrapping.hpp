#ifndef SDL_ENGINE_UI_WRAPPING_HPP
#define SDL_ENGINE_UI_WRAPPING_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "Texture.hpp"

namespace SDLEngine
{
  namespace UI
  {
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
