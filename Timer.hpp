#ifndef SDL_ENGINE_TIMER_HPP
#define SDL_ENGINE_TIMER_HPP

#include <SDL2/SDL.h>
#include <memory>

namespace SDLEngine
{
  class Timer
  {
  public:
    virtual ~Timer() = default;

    virtual void setFPS(int) = 0;
    virtual void startTimer() = 0;
    virtual int updateTimer() = 0;
    virtual int getCurrentFPS() const = 0;

    static std::unique_ptr< Timer > makeDefaultTimer();

  protected:
    Timer() = default;
  };

  class TimerImpl: public Timer
  {
  public:
    TimerImpl();

    void setFPS(int FPS) override;
    void startTimer() override;
    int updateTimer() override;
    int getCurrentFPS() const override;
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
