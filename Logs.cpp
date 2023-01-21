#include "Logs.hpp"
#include <iomanip>

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define WHITE "\033[1;37m"

SDLEngine::Logs SDLEngine::logs = SDLEngine::Logs{};

SDLEngine::LogTag::LogTag(const std::string& s):
  tag{s}
{}

const std::string& SDLEngine::LogTag::str() const
{
  return tag;
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
  if (!l.normal)
  {
    return l;
  }
  l.normal << std::left;
  switch (l.getLevel())
  {
  case LogLevel::ERROR:
    l.error << RED << std::setw(7) << "ERROR ";
    break;
  case LogLevel::INFO:
    l.normal << YELLOW << std::setw(7) << "INFO ";
    break;
  case LogLevel::DEBUG:
    l.normal << std::setw(7) << "DEBUG ";
    break;
  default:
    break;
  }
  l.normal << '[' << std::setw(10) << l.getTag().str() << "] ";
  l.normal << std::setw(100) << msg << RESET << "\n";
  return l;
}
