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

  struct LogTag
  {
    LogTag() = default;
    explicit LogTag(const std::string&);
    const std::string& str() const;

  private:
    std::string tag;
  };

  struct Logs
  {
    std::ostream& normal = std::cout;
    std::ostream& error = std::cerr;

    friend Logs& operator<<(Logs& l, LogLevel level)
    {
      l.level_ = level;
      return l;
    }
    friend Logs& operator<<(Logs& l, const LogTag& tag)
    {
      l.tag_ = tag;
      return l;
    }

    const LogLevel& getLevel() const;
    const LogTag& getTag() const;

  private:
    LogLevel level_;
    LogTag tag_;
  };

  Logs& operator<<(Logs&, const std::string&);

  extern Logs logs;
}

#endif
