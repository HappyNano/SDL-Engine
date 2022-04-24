#ifndef SDL_ENGINE_LOGS_HPP
#define SDL_ENGINE_LOGS_HPP

#include <string>
#include <iostream>

namespace SDLEngine
{
  enum class LogLevel
  {
    ERROR,
    INFO,
    DEBUG
  };

  struct Logs
  {
    static Logs& Instance(std::ostream& stream = std::cout, bool colored = true)
    {
      static Logs singleton{stream, colored};
      return singleton;
    }

    static void print(const std::string&, const std::string&, LogLevel);
    void doPrint(const std::string&, const std::string&, LogLevel);

    std::ostream& ostream;
    bool colored;
  };
}

#endif
