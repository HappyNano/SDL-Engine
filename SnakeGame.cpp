#include "SnakeGame.hpp"
#include "Geometry.hpp"

#include "SDLMethods.hpp"

#include <algorithm>
#include <functional>

#include "Assets.hpp"

Game::SnakeGame::SnakeGame(SDL_Window* window, SDL_Renderer* renderer, int grid_size):
  window_(window),
  renderer_(renderer),
  width_{0},
  height_{0},
  cell_size_{0},
  grid_size_{grid_size},
  running_{false},
  alive_{false},
  cell_{},
  snake_rects_{},
  direction_{Direction::RIGHT},
  apple_{},
  start_game_button_{}
{
  SDL_assert(window && renderer);
  SDL_GetWindowSize(window, &width_, &height_);

  cell_size_ = height_ / grid_size;

  auto tmp_but = new UI::Button{u"Start game", {50, 50, 100, 50}, {"default", 20, {255, 0, 0, 255}}};
  tmp_but->setWrapping(UI::Wrapping::centerEquator);
  tmp_but->setX(width_ / 2 - tmp_but->getWidth() / 2);
  tmp_but->setY(height_ / 2 - tmp_but->getHeight() / 2);
  SDLEngine::UI::Rectangle button_background(tmp_but->getRect(), {0, 0, 200, 200}, 5);
  tmp_but->setBackground(std::move(button_background));
  tmp_but->setFunction(std::bind(&SnakeGame::restartStats, std::addressof(*this)));
  start_game_button_ = std::unique_ptr< UI::Button >(tmp_but);

  running_ = true;
}

int Game::SnakeGame::offset() const
{
  return cell_size_ / 2;
}

void Game::SnakeGame::renderStart()
{
  SDL_RenderClear(renderer_);
  start_game_button_->render(renderer_);
  SDL_RenderPresent(renderer_);
}

void Game::SnakeGame::renderBounds()
{
  SDL_Color prev_color;
  SDL_GetRenderDrawColor(renderer_, &prev_color.r, &prev_color.g, &prev_color.b, &prev_color.a);
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  SDL_RenderDrawLine(renderer_, this->offset(), this->offset(), width_ - this->offset(), this->offset());
  SDL_RenderDrawLine(renderer_, width_ - this->offset(), this->offset(), width_ - this->offset(), height_ - this->offset());
  SDL_RenderDrawLine(renderer_, width_ - this->offset(), height_ - this->offset(), this->offset(), height_ - this->offset());
  SDL_RenderDrawLine(renderer_, this->offset(), height_ - this->offset(), this->offset(), this->offset());
  SDL_SetRenderDrawColor(renderer_, prev_color.r, prev_color.g, prev_color.b, prev_color.a);
}

void Game::SnakeGame::renderGame()
{
  SDL_RenderClear(renderer_);
  for (auto&& cell_rect: snake_rects_)
  {
    cell_.setRect(cell_rect);
    cell_.render(renderer_);
  }
  apple_.render(renderer_);

  renderBounds();

  SDL_RenderPresent(renderer_);
}

void Game::SnakeGame::handleEvents()
{
  Direction new_direction = direction_;
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (!alive_)
    {
      start_game_button_->handleEvent(event);
    }
    switch (event.type)
    {
    case SDL_QUIT:
      running_ = false;
      break;
    case SDL_KEYDOWN: {
      switch (event.key.keysym.sym)
      {
      case SDLK_w: {
        if (direction_ != Direction::DOWN)
        {
          new_direction = Direction::UP;
        }
      }
      break;
      case SDLK_s: {
        if (direction_ != Direction::UP)
        {
          new_direction = Direction::DOWN;
        }
      }
      break;
      case SDLK_a: {
        if (direction_ != Direction::RIGHT)
        {
          new_direction = Direction::LEFT;
        }
      }
      break;
      case SDLK_d: {
        if (direction_ != Direction::LEFT)
        {
          new_direction = Direction::RIGHT;
        }
      }
      break;
      default:
        break;
      }
    }
    }
  }
  direction_ = new_direction;
}

void Game::SnakeGame::restartStats()
{
  snake_rects_.clear();
  cell_ = UI::Rectangle({cell_size_ * 5 + offset(), cell_size_ * 5 + offset(), cell_size_, cell_size_}, {0, 230, 0, 255}, 1);
  snake_rects_.push_front(cell_.getRect());
  cell_.move(-cell_size_, 0);
  snake_rects_.push_front(cell_.getRect());
  direction_ = Direction::RIGHT;

  apple_ = UI::Rectangle({cell_size_ * 6 + offset(), cell_size_ * 6 + offset(), cell_size_, cell_size_}, {230, 0, 0, 255}, 1);

  alive_ = true;
}

void Game::SnakeGame::start()
{
  while (running_)
  {
    if (!alive_)
    {
      renderStart();
    }
    else
    {
      nextStep();
    }
    this->handleEvents();
  }
}

void Game::SnakeGame::nextStep()
{
  if (alive_)
  {
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
      apple_rect.x = cell_size_ * static_cast< int >(std::rand() % (grid_size_ - 1)) + this->offset();
      apple_rect.y = cell_size_ * static_cast< int >(std::rand() % (grid_size_ - 1)) + this->offset();
      apple_.setRect(apple_rect);
    }

    const auto& new_head = snake_rects_.back();
    bool out_of_border = new_head.x < cell_size_ / 2 || new_head.y < cell_size_ / 2 || new_head.x >= std::floor(width_ - cell_size_ / 1.9)
                         || new_head.y >= std::floor(height_ - cell_size_ / 1.9);
    auto equal_rects = [&](const SDL_Rect& rect) {
      return rect == new_head;
    };
    bool intersections = snake_rects_.size() > 1 && std::any_of(snake_rects_.begin(), std::prev(snake_rects_.end()), equal_rects);
    if (out_of_border || intersections)
    {
      alive_ = false;
    }

    renderGame();
    SDL_Delay(67);
  }
}
