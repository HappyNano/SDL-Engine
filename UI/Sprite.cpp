#include "Sprite.hpp"
#include <utility>

SDLEngine::UI::Sprite::Sprite(SDL_Rect)
{}

SDLEngine::UI::Sprite::Sprite(const this_t&)
{
  // SDL_Surface
}
SDLEngine::UI::Sprite::Sprite(this_t&& obj) noexcept:
  texture_(obj.texture_),
  texture_rect_(obj.texture_rect_),
  collide_rect_(obj.collide_rect_),
  scale_(obj.scale_),
  x_(obj.x_),
  y_(obj.y_)
{
  obj.texture_ = nullptr;
  obj.texture_rect_ = {0, 0, 0, 0};
  obj.collide_rect_ = {0, 0, 0, 0};
  obj.scale_ = 0;
  obj.x_ = 0;
  obj.y_ = 0;
}

SDLEngine::UI::Sprite::~Sprite()
{
  if (texture_)
  {
    SDL_DestroyTexture(texture_);
  }
}

SDLEngine::UI::Sprite::this_t& SDLEngine::UI::Sprite::operator=(const this_t& obj)
{
  if (this != std::addressof(obj))
  {
    this_t temp(obj);
    swap(temp);
  }
  return *this;
}
SDLEngine::UI::Sprite::this_t& SDLEngine::UI::Sprite::operator=(this_t&& obj) noexcept
{
  if (this != std::addressof(obj))
  {
    this_t temp(std::move(obj));
    swap(temp);
  }
  return *this;
}

void SDLEngine::UI::Sprite::swap(this_t& obj) noexcept
{
  std::swap(texture_, obj.texture_);
  std::swap(texture_rect_, obj.texture_rect_);
  std::swap(collide_rect_, obj.collide_rect_);
  std::swap(scale_, obj.scale_);
  std::swap(x_, obj.x_);
  std::swap(y_, obj.y_);
}
