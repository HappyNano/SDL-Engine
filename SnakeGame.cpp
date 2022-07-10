#include "SnakeGame.hpp"
#include "Geometry.hpp"

#include "SDLMethods.hpp"

Game::SnakeGame::SnakeGame(SDL_Window* window, SDL_Renderer* renderer, int grid_size):
  window_(window),
  renderer_(renderer),
  width_{0},
  height_{0},
  cell_size_{0},
  grid_size_{grid_size},
  running_{false},
  cell_{},
  snake_rects_{},
  direction_{Direction::RIGHT},
  apple_{}
{
  SDL_assert(window && renderer);
  SDL_GetWindowSize(window, &width_, &height_);

  cell_size_ = height_ / grid_size;

  cell_ = UI::Rectangle({cell_size_ * 5, cell_size_ * 5, cell_size_, cell_size_}, {0, 230, 0, 255}, 1);
  snake_rects_.push_front(cell_.getRect());
  cell_.move(-cell_size_, 0);
  snake_rects_.push_front(cell_.getRect());

  apple_ = UI::Rectangle({cell_size_ * 6, cell_size_ * 6, cell_size_, cell_size_}, {230, 0, 0, 255}, 1);

  running_ = true;
}

void Game::SnakeGame::start()
{
  while (running_)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        running_ = false;
        break;
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
          direction_ = Direction::UP;
          break;
        case SDLK_s:
          direction_ = Direction::DOWN;
          break;
        case SDLK_a:
          direction_ = Direction::LEFT;
          break;
        case SDLK_d:
          direction_ = Direction::RIGHT;
          break;
        default:
          break;
        }
      }
      }
    }

    SDL_Rect offset{0, 0, 0, 0};

    switch (direction_)
    {
    case Direction::UP:
      offset.y = -cell_size_;
      break;
    case Direction::DOWN:
      offset.y = cell_size_;
      break;
    case Direction::LEFT:
      offset.x = -cell_size_;
      break;
    case Direction::RIGHT:
      offset.x = cell_size_;
      break;
    default:
      break;
    }

    SDL_Rect tmp_rect = snake_rects_.front();
    if (snake_rects_.size() > 1)
    {
      for (size_t i = 0; i < snake_rects_.size() - 1; ++i)
      {
        snake_rects_.at(i) = snake_rects_.at(i + 1);
      }
    }
    snake_rects_.back() += {offset.x, offset.y};
    
    // Check collide with apple
    SDL_Rect apple_rect = apple_.getRect();
    if (snake_rects_.back() == apple_rect)
    {
      snake_rects_.push_front(tmp_rect);
      apple_rect.x = cell_size_ * static_cast< int >(std::rand() % grid_size_);
      apple_rect.y = cell_size_ * static_cast< int >(std::rand() % grid_size_);
      apple_.setRect(apple_rect);
    }

    SDL_RenderClear(renderer_);
    for (auto&& cell_rect: snake_rects_)
    {
      cell_.setRect(cell_rect);
      cell_.render(renderer_);
    }
    apple_.render(renderer_);
    SDL_RenderPresent(renderer_);
    SDL_Delay(200);
  }
}
