#include "Assets.hpp"
#include <SDL2/SDL_image.h>
#include <stdexcept>

bool SDLEngine::Assets::checkAndSaveTextures(SDL_Renderer* renderer, const std::string& texture_name, const std::string& path)
{
  try
  {
    SDL_Texture* texture = nullptr;
    if (path.find(".bmp") != std::string::npos)
    {
      texture = Assets::LoadBMP(renderer, path.c_str());
    }
    else
    {
      texture = Assets::LoadPNG(renderer, path.c_str());
    }
    SDL_DestroyTexture(texture);
    assets_names_.insert({texture_name, path});
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
    TTF_CloseFont(font);
    assets_names_.insert({font_name, path});
  }
  catch (const std::logic_error&)
  {
    return false;
  }
  return true;
}

SDL_Texture* SDLEngine::Assets::getTextureByName(SDL_Renderer* renderer, const std::string& texture_name)
{
  std::string path = assets_names_[texture_name];
  if (path.find(".bmp") != std::string::npos)
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
  return Assets::LoadFont(assets_names_[font_name]);
}

SDL_Texture* SDLEngine::Assets::LoadBMP(SDL_Renderer* renderer, const char* filename)
{
  SDL_Surface* loaded_image = SDL_LoadBMP(filename);
  if (!loaded_image)
  {
    throw std::logic_error("Failed to load image!");
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loaded_image);
  SDL_FreeSurface(loaded_image);

  return texture;
}

SDL_Texture* SDLEngine::Assets::LoadPNG(SDL_Renderer* renderer, const char* filename)
{
  SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
  if (!texture)
  {
    throw std::logic_error("Failed to load image!");
  }
  return texture;
}

TTF_Font* SDLEngine::Assets::LoadFont(const char* filename, int size)
{
  TTF_Font* font = LoadFont(filename, size);
  if (!font)
  {
    throw std::logic_error("Failed to load font!");
  }
  return font;
}
