#include "Texture.hpp"
#include <iostream>
#include <utility>

SDLEngine::UI::Texture::Texture(SDL_Texture* texture, const SDL_Rect& rect):
  texture_(texture),
  rect_(rect)
{}

SDLEngine::UI::Texture::Texture(SDL_Texture* texture):
  texture_(texture)
{
  rect_.x = 0;
  rect_.y = 0;
  SDL_QueryTexture(texture, NULL, NULL, &rect_.w, &rect_.h);
}

SDLEngine::UI::Texture::Texture(this_t&& obj) noexcept:
  texture_(obj.texture_),
  rect_(obj.rect_)
{
  obj.texture_ = nullptr;
  obj.rect_ = {};
}

SDLEngine::UI::Texture::~Texture()
{
  if (texture_)
  {
    SDL_DestroyTexture(texture_);
  }
}

SDLEngine::UI::Texture::this_t& SDLEngine::UI::Texture::operator=(this_t&& obj) noexcept
{
  if (this != std::addressof(obj))
  {
    this_t temp(std::move(obj));
    swap(temp);
  }
  return *this;
}

void SDLEngine::UI::Texture::swap(this_t& obj) noexcept
{
  std::swap(texture_, obj.texture_);
  std::swap(rect_, obj.rect_);
}

void SDLEngine::UI::Texture::render(SDL_Renderer* renderer)
{
  if (!texture_)
  {
    std::cerr << "ERROR [EngineSDL][Texture]: texture is nullptr" << std::endl;
    return;
  }
  SDL_RenderCopy(renderer, texture_, NULL, &rect_);
}
