#pragma once

#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>

class Timestamper {
  public:
    static std::string GetCurrent();
};
