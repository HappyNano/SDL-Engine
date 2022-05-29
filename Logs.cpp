#include "Logs.hpp"
#include <iomanip>

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define WHITE "\033[1;37m"

SDLEngine::Logs& SDLEngine::Logs::Instance(std::ostream& stream, bool colored)
{
  static Logs singleton{stream, colored};
  return singleton;
}

void SDLEngine::Logs::print(const std::string& tag, const std::string& text, LogLevel level)
{
  Instance().doPrint(tag, text, level);
}

void SDLEngine::Logs::doPrint(const std::string& tag, const std::string& text, LogLevel level)
{
  if (!ostream)
  {
    return;
  }
  ostream << std::left;
  switch (level)
  {
  case LogLevel::ERROR:
    ostream << RED << std::setw(7) << "ERROR ";
    break;
  case LogLevel::INFO:
    ostream << YELLOW << std::setw(7) << "INFO ";
    break;
  case LogLevel::DEBUG:
    ostream << std::setw(7) << "DEBUG ";
    break;
  default:
    break;
  }
  ostream << '[' << std::setw(10) << tag << "] ";
  ostream << std::setw(100) << text << RESET << "\n";
}
