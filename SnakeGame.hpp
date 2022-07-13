#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <SDL2/SDL.h>
#include <deque>
#include <memory>

#include <UI/Rectangle.hpp>
#include <UI/Button.hpp>

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
    SnakeGame(SDL_Window*, SDL_Renderer*, int);
    ~SnakeGame() = default;

    void start();

  protected:
    int offset() const;
    void renderStart();
    void renderBounds();
    void renderGame();
    void handleEvents();
    void restartStats();

    void nextStep();

    void setAlive(bool);

  private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;

    int width_;
    int height_;
    int cell_size_;
    int grid_size_;

    bool running_;
    bool alive_;

    UI::Rectangle cell_;
    std::deque< SDL_Rect > snake_rects_;
    Direction direction_;

    UI::Rectangle apple_;

    std::unique_ptr< UI::Button > start_game_button_;
  };
}

#endif
