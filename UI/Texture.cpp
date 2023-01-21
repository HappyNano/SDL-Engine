#include "Texture.hpp"
#include <utility>
#include "SDLMethods.hpp"
#include "Logs.hpp"

SDLEngine::UI::Texture::Texture():
  texture_(nullptr),
  rect_()
{}

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

SDLEngine::UI::Texture::Texture(SDL_Renderer* renderer, SDL_Surface* surf):
  Texture(SDL_CreateTextureFromSurface(renderer, surf), {0, 0, surf->w, surf->h})
{}

SDLEngine::UI::Texture::Texture(SDL_Renderer* renderer, Surface&& surf):
  Texture(surf.createTexture(renderer), surf.getRect())
{}

SDLEngine::UI::Texture::Texture(this_t&& obj) noexcept:
  texture_(obj.texture_),
  rect_(obj.rect_)
{
  obj.texture_ = nullptr;
  obj.rect_ = {};
}

SDLEngine::UI::Texture::~Texture()
{
  erase();
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

void SDLEngine::UI::Texture::move(int offset_x, int offset_y)
{
  rect_ += {offset_x, offset_y};
}

void SDLEngine::UI::Texture::render(SDL_Renderer* renderer)
{
  if (!texture_)
  {
    logs << LogLevel::ERROR << LogTag{"Texture"} << "This texture cannot be rendered (nullptr)!";
    return;
  }
  SDL_RenderCopy(renderer, texture_, NULL, &rect_);
}

bool SDLEngine::UI::Texture::valid() const
{
  return texture_;
}

void SDLEngine::UI::Texture::erase()
{
  if (texture_)
  {
    SDL_DestroyTexture(texture_);
  }
  texture_ = nullptr;
}
