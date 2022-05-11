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

void SDLEngine::UI::Rectangle::setWidth(int width)
{
  texture_.rect_.w = width;
}
void SDLEngine::UI::Rectangle::setHeight(int height)
{
  texture_.rect_.h = height;
}
void SDLEngine::UI::Rectangle::setX(int x)
{
  move(x - getX(), 0);
}
void SDLEngine::UI::Rectangle::setY(int y)
{
  move(0, y - getY());
}
void SDLEngine::UI::Rectangle::move(int offset_x, int offset_y)
{
  texture_.move(offset_x, offset_y);
}
void SDLEngine::UI::Rectangle::setRect(const SDL_Rect& rect)
{
  texture_.rect_ = rect;
}

void SDLEngine::UI::Rectangle::setColor(SDL_Color color)
{
  if (color == color_)
  {
    return;
  }
  color_ = color;
  reRender();
}
void SDLEngine::UI::Rectangle::setRadius(int round_radius)
{
  if (round_radius == round_radius_)
  {
    return;
  }
  if (round_radius < 0)
  {
    Logs::print("Rectangle", "Round radius must be non-negative!", LogLevel::ERROR);
    throw std::logic_error("Round radius must be non-negative!");
  }
  round_radius_ = round_radius;
  reRender();
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
  return texture_.rect_;
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
