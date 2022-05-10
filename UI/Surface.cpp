#include "Surface.hpp"
#include <iostream>
#include <utility>
#include "SDLMethods.hpp"
#include "Logs.hpp"

SDLEngine::UI::Surface::Surface():
  surface_(nullptr)
{}

SDLEngine::UI::Surface::Surface(SDL_Surface* surface):
  surface_(surface)
{}

SDLEngine::UI::Surface::Surface(this_t&& obj) noexcept:
  surface_(obj.surface_)
{
  obj.surface_ = nullptr;
}

SDLEngine::UI::Surface::~Surface()
{
  if (surface_)
  {
    SDL_FreeSurface(surface_);
  }
}

SDLEngine::UI::Surface::this_t& SDLEngine::UI::Surface::operator=(this_t&& obj) noexcept
{
  if (std::addressof(obj) != this)
  {
    this_t temp(std::move(obj));
    swap(temp);
  }
  return *this;
}

void SDLEngine::UI::Surface::swap(this_t& obj) noexcept
{
  std::swap(surface_, obj.surface_);
}

SDL_Texture* SDLEngine::UI::Surface::createTexture(SDL_Renderer* renderer)
{
  if (!surface_)
  {
    Logs::print("Surface", "Texture cannot be crated from this surface!", LogLevel::ERROR);
  }
  return SDL_CreateTextureFromSurface(renderer, surface_);
}

SDL_Rect SDLEngine::UI::Surface::getRect() const
{
  return {0, 0, surface_->w, surface_->h};
}

bool SDLEngine::UI::Surface::valid() const
{
  return surface_;
}
