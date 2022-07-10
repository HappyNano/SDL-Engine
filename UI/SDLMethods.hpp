#ifndef SDL_ENGINE_UI_SDL_METHODS_HPP
#define SDL_ENGINE_UI_SDL_METHODS_HPP

#include <SDL2/SDL.h>
#include <utility>

namespace SDLEngine
{
  SDL_Rect& operator+=(SDL_Rect&, const std::pair< int, int >&);
  bool operator==(const SDL_Rect&, const SDL_Rect&);
  bool operator==(const SDL_Color&, const SDL_Color&);
}

#endif
