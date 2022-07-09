#include "SnakeGame.hpp"

Game::SnakeGame::SnakeGame(SDL_Window* window, SDL_Renderer* renderer):
  window_(window),
  renderer_(renderer),
  width_(0),
  height_(0),
  running_(false)
{
  SDL_assert(window && renderer);
  SDL_GetWindowSize(window, &width_, &height_);

  running_ = true;
}

void Game::SnakeGame::start()
{
  while (running_)
  {
    
  }
}

