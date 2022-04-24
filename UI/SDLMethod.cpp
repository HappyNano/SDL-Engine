#include "SDLMethods.hpp"

SDL_Rect& SDLEngine::operator+=(SDL_Rect& rect, const std::pair< int, int >& offset)
{
  rect.x += offset.first;
  rect.y += offset.second;
}
