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

    explicit LogTag(const std::string& s):
      tag{s}
    {}

    const std::string& str() const
    {
      return tag;
    }

  private:
    std::string tag;
  };

  struct LogsBase
  {
    static void print(const std::string&, const std::string&, LogLevel);
    void doPrint(const std::string&, const std::string&, LogLevel);

  protected:
    static LogsBase& Instance();

    std::ostream& normal = std::cout;
    std::ostream& error = std::cerr;
    bool colored;
  };

  struct Logs
  {
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
