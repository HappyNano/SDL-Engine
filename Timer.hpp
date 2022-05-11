#ifndef SDL_ENGINE_TIMER_HPP
#define SDL_ENGINE_TIMER_HPP

#include <SDL2/SDL.h>

namespace SDLEngine
{
  class Timer
  {
  public:
    Timer();

    void setFPS(int FPS);
    void startTimer();
    void updateTimer();
    int getCurrentFPS() const;
    float getDT() const;

  private:
    int FPS_num;
    int FPS_i;

    int FPS;
    float FPS_ms;
    float dT;
    Uint32 start_time;
    Uint32 end_time;
  };
}

#endif
