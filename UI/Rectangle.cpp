#include "Rectangle.hpp"
#include <utility>
#include <stdexcept>
#include "Geometry.hpp"
#include "SDLMethods.hpp"
#include "Logs.hpp"

SDLEngine::UI::Rectangle::Rectangle(SDL_Rect rect, SDL_Color color, int round_radius):
  color_(color),
  round_radius_(round_radius),
  rect_(rect),
  surface_(),
  texture_()
{
  reRender();
}

SDLEngine::UI::Rectangle::Rectangle(this_t&& obj) noexcept:
  color_(obj.color_),
  round_radius_(obj.round_radius_),
  rect_(obj.rect_),
  surface_(std::move(obj.surface_)),
  texture_(std::move(obj.texture_))
{}
typename SDLEngine::UI::Rectangle::this_t& SDLEngine::UI::Rectangle::operator=(this_t&& obj) noexcept
{
  if (std::addressof(obj) != this)
  {
    this_t tmp(std::move(obj));
    swap(tmp);
  }
  return *this;
}
void SDLEngine::UI::Rectangle::swap(this_t& obj) noexcept
{
  std::swap(color_, obj.color_);
  std::swap(round_radius_, obj.round_radius_);
  std::swap(rect_, obj.rect_);
  std::swap(surface_, obj.surface_);
  std::swap(texture_, obj.texture_);
}

typename SDLEngine::UI::Rectangle::this_t& SDLEngine::UI::Rectangle::setWidth(int width)
{
  texture_.rect_.w = width;
  return *this;
}
typename SDLEngine::UI::Rectangle::this_t& SDLEngine::UI::Rectangle::setHeight(int height)
{
  texture_.rect_.h = height;
  return *this;
}
typename SDLEngine::UI::Rectangle::this_t& SDLEngine::UI::Rectangle::setX(int x)
{
  move(x - getX(), 0);
  return *this;
}
typename SDLEngine::UI::Rectangle::this_t& SDLEngine::UI::Rectangle::setY(int y)
{
  move(0, y - getY());
  return *this;
}
typename SDLEngine::UI::Rectangle::this_t& SDLEngine::UI::Rectangle::move(int offset_x, int offset_y)
{
  texture_.move(offset_x, offset_y);
  rect_ += {offset_x, offset_y};
  return *this;
}
typename SDLEngine::UI::Rectangle::this_t& SDLEngine::UI::Rectangle::setRect(const SDL_Rect& rect)
{
  rect_ = rect;
  texture_.rect_ = rect_;
  return *this;
}

typename SDLEngine::UI::Rectangle::this_t& SDLEngine::UI::Rectangle::setColor(SDL_Color color)
{
  if (color == color_)
  {
    return *this;
  }
  color_ = color;
  reRender();
  return *this;
}
typename SDLEngine::UI::Rectangle::this_t& SDLEngine::UI::Rectangle::setRadius(int round_radius)
{
  if (round_radius == round_radius_)
  {
    return *this;
  }
  if (round_radius < 0)
  {
    Logs::print("Rectangle", "Round radius must be non-negative!", LogLevel::ERROR);
    throw std::logic_error("Round radius must be non-negative!");
  }
  round_radius_ = round_radius;
  reRender();
  return *this;
}

int SDLEngine::UI::Rectangle::getWidth() const
{
  return getRect().w;
}
int SDLEngine::UI::Rectangle::getHeight() const
{
  return getRect().h;
}
int SDLEngine::UI::Rectangle::getX() const
{
  return getRect().x;
}
int SDLEngine::UI::Rectangle::getY() const
{
  return getRect().y;
}
const SDL_Rect& SDLEngine::UI::Rectangle::getRect() const
{
  return rect_;
}

void SDLEngine::UI::Rectangle::handleEvent(const SDL_Event&)
{}

void SDLEngine::UI::Rectangle::render(SDL_Renderer* renderer)
{
  if (!texture_.valid())
  {
    texture_ = Texture(renderer, std::move(surface_));
    texture_.rect_ = rect_;
  }
  texture_.render(renderer);
}

void SDLEngine::UI::Rectangle::reRender()
{
  SDL_Surface* new_surface = SDL_CreateRGBSurface(0, rect_.w, rect_.h, 32, RMASK, GMASK, BMASK, AMASK);
  Uint32 color_alpha = SDL_MapRGBA(new_surface->format, 255, 255, 255, 0);
  SDL_Rect rect_alpha{0, 0, rect_.w, rect_.h};
  SDL_FillRect(new_surface, std::addressof(rect_alpha), color_alpha);
  Uint32 color = SDL_MapRGBA(new_surface->format, color_.r, color_.g, color_.b, color_.a);
  draw_FillRoundedRectangle(new_surface, 0, 0, rect_.w, rect_.h, round_radius_, color);
  surface_ = Surface(new_surface);
  texture_ = Texture();
}
