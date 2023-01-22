#include "Assets.hpp"
#include <SDL2/SDL_image.h>
#include <stdexcept>

#define CHECK(x, msg) if (x) { throw std::logic_error(msg); } 

namespace
{
  bool isStringConsist(const std::string& str, const std::string& sought)
  {
    return str.find(sought) != std::string::npos;
  }

  bool isBmpFile(const std::string& str)
  {
    return isStringConsist(str, ".bmp");
  }
}

bool SDLEngine::Assets::checkAndSaveTextures(SDL_Renderer* renderer, const std::string& texture_name, const std::string& path)
{
  try
  {
    SDL_Texture* texture = nullptr;
    if (isBmpFile(path))
    {
      texture = Assets::LoadBMP(renderer, path.c_str());
    }
    else
    {
      texture = Assets::LoadPNG(renderer, path.c_str());
    }
    SDL_DestroyTexture(texture);
    Instance().assets_names_.insert({texture_name, path});
  }
  catch (const std::logic_error&)
  {
    return false;
  }
  return true;
}

bool SDLEngine::Assets::checkAndSaveFonts(const std::string& font_name, const std::string& path, int size)
{
  try
  {
    TTF_Font* font = Assets::LoadFont(path.c_str(), size);
    if (!font)
    {
      return false;
    }
    TTF_CloseFont(font);
    Instance().assets_names_.insert({font_name, path});
  }
  catch (const std::logic_error&)
  {
    return false;
  }
  return true;
}

SDL_Texture* SDLEngine::Assets::getTextureByName(SDL_Renderer* renderer, const std::string& texture_name)
{
  std::string path = Instance().assets_names_[texture_name];
  if (isBmpFile(path))
  {
    return Assets::LoadBMP(renderer, path.c_str());
  }
  else
  {
    return Assets::LoadPNG(renderer, path.c_str());
  }
}

TTF_Font* SDLEngine::Assets::getFontByName(const std::string& font_name, int size)
{
  return Assets::LoadFont(Instance().assets_names_.at(font_name).c_str(), size);
}

SDL_Texture* SDLEngine::Assets::LoadBMP(SDL_Renderer* renderer, const char* filename)
{
  SDL_Surface* loaded_image = SDL_LoadBMP(filename);
  CHECK(!loaded_image, "Failed to load image!");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loaded_image);
  SDL_FreeSurface(loaded_image);
  return texture;
}

SDL_Texture* SDLEngine::Assets::LoadPNG(SDL_Renderer* renderer, const char* filename)
{
  SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
  CHECK(!texture, "Failed to load image!");
  return texture;
}

TTF_Font* SDLEngine::Assets::LoadFont(const char* filename, int size)
{
  TTF_Font* font = TTF_OpenFont(filename, size);
  CHECK(!font, "Failed to load font!");
  return font;
}
