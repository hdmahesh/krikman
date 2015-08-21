#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <sstream>

#ifdef __DEBUG__
#define FFL {std::cout << __FILE__ << " : " << __FUNCTION__ << ":" << __LINE__ << std::endl;}
#else
#define FFL
#endif

namespace utility
{
  bool getUnsignedFromString(std::string str, unsigned &in);
  bool getIntegerFromString(std::string str, int &in);

  // Environment Variable Access APIs
  int envGetIntegerVar(const std::string &env_str, int default_value);
}

#endif
