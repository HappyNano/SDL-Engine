#include "Geometry.hpp"

void SDLEngine::UI::set_pixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
  Uint32* const target_pixel
      = reinterpret_cast< Uint32* >((static_cast< Uint8* >(surface->pixels)) + y * surface->pitch + x * surface->format->BytesPerPixel);
  *target_pixel = pixel;
}

void SDLEngine::UI::DrawCircle(SDL_Surface* surface, int32_t centreX, int32_t centreY, int32_t radius, Uint32 pixel)
{
  for (int x = centreX - radius; x < centreX + radius; x++)
  {
    for (int y = centreY - radius; y < centreY + radius; y++)
    {
      if (std::sqrt((centreX - x) * (centreX - x) + (centreY - y) * (centreY - y)) < radius)
      {
        set_pixel(surface, x, y, pixel);
      }
    }
  }
}

void SDLEngine::UI::DrawRectangle(SDL_Surface* surface, int32_t x, int32_t y, int32_t w, int32_t h, Uint32 color)
{
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  SDL_FillRect(surface, &rect, color);
}

void SDLEngine::UI::draw_FillRoundedRectangle(SDL_Surface* surface, int, int, int w, int h, int radius, Uint32 color)
{
  DrawRectangle(surface, radius, 0, w - 2 * radius, h, color);
  DrawRectangle(surface, 0, radius, w, h - 2 * radius, color);
  DrawCircle(surface, radius, radius, radius, color);
  DrawCircle(surface, w - radius, radius, radius, color);
  DrawCircle(surface, radius, h - radius, radius, color);
  DrawCircle(surface, w - radius, h - radius, radius, color);
}

void SDLEngine::UI::draw_GradientRectangle(SDL_Surface* surface, int x, int y, int w, int h, Uint32 begin_color, Uint32 end_color)
{
  SDL_Color begin_color_;
  SDL_GetRGBA(begin_color, surface->format, &begin_color_.r, &begin_color_.g, &begin_color_.b, &begin_color_.a);

  SDL_Color end_color_;
  SDL_GetRGBA(end_color, surface->format, &end_color_.r, &end_color_.g, &end_color_.b, &end_color_.a);

  float r = 1.f * std::abs(end_color_.r - begin_color_.r) / (w - x);
  float g = 1.f * std::abs(end_color_.g - begin_color_.g) / (w - x);
  float b = 1.f * std::abs(end_color_.b - begin_color_.b) / (w - x);
  for (int i = x; i < w; i++)
  {
    for (int j = y; j < h; j++)
    {
      Uint32 temp_color = SDL_MapRGBA(surface->format, std::abs(end_color_.r - r * (w - i)), std::abs(end_color_.g - g * (w - i)),
                                      std::abs(end_color_.b - b * (w - i)), 255);
      set_pixel(surface, i, j, temp_color);
    }
  }
}