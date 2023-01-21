#include "Logs.hpp"
#include <iomanip>

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define WHITE "\033[1;37m"

SDLEngine::Logs SDLEngine::logs = SDLEngine::Logs{};

SDLEngine::LogsBase& SDLEngine::LogsBase::Instance()
{
  static LogsBase singleton;
  return singleton;
}

void SDLEngine::LogsBase::print(const std::string& tag, const std::string& text, LogLevel level)
{
  Instance().doPrint(tag, text, level);
}

void SDLEngine::LogsBase::doPrint(const std::string& tag, const std::string& text, LogLevel level)
{
  if (!normal)
  {
    return;
  }
  normal << std::left;
  switch (level)
  {
  case LogLevel::ERROR:
    normal << RED << std::setw(7) << "ERROR ";
    break;
  case LogLevel::INFO:
    normal << YELLOW << std::setw(7) << "INFO ";
    break;
  case LogLevel::DEBUG:
    normal << std::setw(7) << "DEBUG ";
    break;
  default:
    break;
  }
  normal << '[' << std::setw(10) << tag << "] ";
  normal << std::setw(100) << text << RESET << "\n";
}

const SDLEngine::LogLevel& SDLEngine::Logs::getLevel() const
{
  return level_;
}

const SDLEngine::LogTag& SDLEngine::Logs::getTag() const
{
  return tag_;
}

SDLEngine::Logs& SDLEngine::operator<<(Logs& l, const std::string& msg)
{
  SDLEngine::LogsBase::print(l.getTag().str(), msg, l.getLevel());
  return l;
}
