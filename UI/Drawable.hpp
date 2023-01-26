#ifndef SDL_ENGINE_UI_DRAWABLE_HPP
#define SDL_ENGINE_UI_DRAWABLE_HPP

#include <SDL2/SDL.h>

namespace SDLEngine
{
  namespace UI
  {
    class Drawable
    {
    public:
      virtual ~Drawable() = default;

      virtual void render(SDL_Renderer*) = 0;

    protected:
      Drawable() = default;
    };
  }
}

#endif
