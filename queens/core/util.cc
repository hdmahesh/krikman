#include "util.h"
#include <sstream>
#include <cstdlib>

namespace utility
{

  bool
  getUnsignedFromString(std::string str, unsigned &in)
  {
    std::stringstream ss(str);
    bool invalid = true;
  
    if (ss >> in) {
      invalid = false;
      char c;
      if (ss >> c) {
        invalid = true;
      }
    }
  
    return invalid;
  }

  bool
  getIntegerFromString(std::string str, int &in)
  {
    std::stringstream ss(str);
    bool invalid = true;
  
    if (ss >> in) {
      invalid = false;
      char c;
      if (ss >> c) {
        invalid = true;
      }
    }
  
    return invalid;
  }

  int
  envGetIntegerVar(const std::string &env_str, int default_value)
  {
    int return_value = default_value;

    char *env_value = getenv(env_str.c_str());
    if (env_value) {
      int converted_value;
      if (!getIntegerFromString(env_value, converted_value)) {
        return_value = converted_value;
      }
    }
    return return_value;
  }
}
