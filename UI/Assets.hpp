#ifndef SDL_ENGINE_ASSETS_HPP
#define SDL_ENGINE_ASSETS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <map>

namespace SDLEngine
{
  class Assets
  {
  public:
    static Assets& Instance()
    {
      static Assets singleton;
      return singleton;
    }

    static bool checkAndSaveTextures(SDL_Renderer*, const std::string&, const std::string&);
    static bool checkAndSaveFonts(const std::string&, const std::string&, int);
    static SDL_Texture* getTextureByName(SDL_Renderer*, const std::string&);
    static TTF_Font* getFontByName(const std::string&, int);

    static SDL_Texture* LoadBMP(SDL_Renderer* renderer, const char* filename);
    static SDL_Texture* LoadPNG(SDL_Renderer* renderer, const char* filename);
    static TTF_Font* LoadFont(const char* filename, int size);

  private:
    Assets() = default;
    ~Assets() = default;
    Assets(const Assets&) = default;
    Assets& operator=(const Assets&) = default;

    std::map< std::string, std::string > assets_names_;
  };
}

#endif
