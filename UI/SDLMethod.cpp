#include "SDLMethods.hpp"

SDL_Rect& SDLEngine::operator+=(SDL_Rect& rect, const std::pair< int, int >& offset)
{
  rect.x += offset.first;
  rect.y += offset.second;
  return rect;
}

bool SDLEngine::operator==(const SDL_Color& first, const SDL_Color& second)
{
  return first.r == second.r && first.g == second.g && first.b == second.b && first.a == second.a;
}
