#include "Timer.hpp"

SDLEngine::Timer::Timer():
  FPS_num(0),
  FPS_i(0),
  FPS(60),
  FPS_ms(1000.f / 60.f),
  dT(0.f),
  start_time(0),
  end_time(0)
{
  start_time = SDL_GetTicks();
  end_time = SDL_GetTicks();
}

void SDLEngine::Timer::startTimer()
{
  start_time = SDL_GetTicks();
  end_time = SDL_GetTicks();
}

void SDLEngine::Timer::updateTimer()
{
  end_time = SDL_GetTicks();

  if (end_time - start_time < FPS_ms)
  {
    SDL_Delay(FPS_ms - end_time + start_time);
  }

  dT = (SDL_GetTicks() - start_time) / 1000.f;

  if (FPS_i >= 50)
  {
    FPS_i = 0;
    FPS_num = 0;
  }

  FPS_num += 1.f / ((SDL_GetTicks() - start_time) / 1000.f);
  FPS_i += 1;

  start_time = SDL_GetTicks();
}

int SDLEngine::Timer::getCurrentFPS() const
{
  return FPS_num / FPS_i;
}

float SDLEngine::Timer::getDT() const
{
  return dT;
}

void SDLEngine::Timer::setFPS(int FPS)
{
  this->FPS = FPS;
  FPS_ms = 1000.f / this->FPS;
}
