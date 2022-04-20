#ifndef SDL_ENGINE_UI_GEOMETRY_HPP
#define SDL_ENGINE_UI_GEOMETRY_HPP

#include <SDL2/SDL.h>

namespace SDLEngine
{
  namespace UI
  {
    void set_pixel(SDL_Surface*, int, int, Uint32);
    void DrawCircle(SDL_Surface*, int32_t, int32_t, int32_t, Uint32);
    void DrawRectangle(SDL_Surface*, int32_t, int32_t, int32_t, int32_t, Uint32);
    void draw_FillRoundedRectangle(SDL_Surface*, int, int, int, int, int, Uint32);
    void draw_GradientRectangle(SDL_Surface*, int, int, int, int, Uint32, Uint32);
  }
}

#endif