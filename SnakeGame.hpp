#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <SDL2/SDL.h>

#include "Game/Sprite.hpp"

namespace Game
{
  class SnakeGame
  {
  public:
    SnakeGame(SDL_Window*, SDL_Renderer*);
    ~SnakeGame();

    void start();

  private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;

    int width_;
    int height_;
    
    bool running_;
  };
}

#endif
