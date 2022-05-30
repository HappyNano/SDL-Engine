#include "Sprite.hpp"
#include <utility>

SDLEngine::Game::Sprite::Sprite(UI::Texture&& texture):
  texture_(std::move(texture)),
  collide_rect_(texture_.rect_),
  scale_(1.f),
  x_(texture_.rect_.x),
  y_(texture_.rect_.y)
{}

void SDLEngine::Game::Sprite::render(SDL_Renderer* renderer)
{
  texture_.render(renderer);
}

void SDLEngine::Game::Sprite::scale(double new_scale)
{
  texture_.rect_.w = texture_.rect_.w * (new_scale / scale_);
  texture_.rect_.h = texture_.rect_.h * (new_scale / scale_);
  collide_rect_.w = collide_rect_.w * (new_scale / scale_);
  collide_rect_.h = collide_rect_.h * (new_scale / scale_);

  scale_ = new_scale;
}

void SDLEngine::Game::Sprite::move(double offset_x, double offset_y)
{
  x_ += offset_x;
  y_ += offset_y;
  correctCoordinates();
}

bool SDLEngine::Game::Sprite::checkCollide(const SDL_Rect& rect) const
{
  return SDL_IntersectRect(std::addressof(collide_rect_), std::addressof(rect), NULL);
}

bool SDLEngine::Game::Sprite::checkCollide(const this_t& obj) const
{
  return checkCollide(obj.collide_rect_);
}

void SDLEngine::Game::Sprite::correctCoordinates()
{
  int offset_x = x_ - texture_.rect_.x;
  int offset_y = y_ - texture_.rect_.y;

  texture_.rect_.x += offset_x;
  texture_.rect_.y += offset_y;

  collide_rect_.x += offset_x;
  collide_rect_.y += offset_y;
}
