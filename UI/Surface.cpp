#include "Surface.hpp"
#include <iostream>
#include <utility>
#include "SDLMethods.hpp"

SDLEngine::UI::Surface::Surface(SDL_Surface* surface):
  surface_(surface)
{}

SDLEngine::UI::Surface::~Surface()
{
  if (surface_)
  {
    SDL_FreeSurface(surface_);
  }
}

SDL_Texture* SDLEngine::UI::Surface::createTexture(SDL_Renderer* renderer)
{
  return SDL_CreateTextureFromSurface(renderer, surface_);
}

SDL_Rect SDLEngine::UI::Surface::getRect() const
{
  return {0, 0, surface_->w, surface_->h};
}
