#pragma once

#include <time.h>
#include <iomanip>
#include <string>
#include <sstream>

class Timestamper {
  public:
    static std::string GetCurrent();
};
