#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <SDL2/SDL.h>
#include <deque>

#include <UI/Rectangle.hpp>

namespace Game
{
  using namespace SDLEngine;

  enum class Direction
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  class SnakeGame
  {
  public:
    SnakeGame(SDL_Window*, SDL_Renderer*);
    ~SnakeGame() = default;

    void start();

  private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;

    int width_;
    int height_;
    int cell_size_;
    
    bool running_;
  
    UI::Rectangle cell_;
    std::deque< SDL_Rect > snake_rects_;
    Direction direction_;
  };
}

#endif
