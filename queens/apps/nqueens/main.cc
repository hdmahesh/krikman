#include <iostream>
#include "src/Queen.h"
#include "src/include/util.h"

int
main (int argc, char *argv[])
{
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <num_of_queens> <num_of_runs>" << std::endl;
    exit(1);
  }

  unsigned num_of_q = 0;
  if (utility::getUnsignedFromString(argv[1], num_of_q)) {
    std::cerr << "Error: invalid number '" << argv[1] << "' of queens specified" << std::endl;
    exit(1);
  }

  unsigned total = 0;
  if (utility::getUnsignedFromString(argv[2], total)) {
    std::cerr << "Error: invalid number '" << argv[2] << "' of runs specified" << std::endl;
    exit(1);
  }

  int success = 0;
  int failure = 0;

  for (size_t index = 0; index < total; ++index) {
    Queen obj(num_of_q);
    if (obj.solve()) {
      ++success;
      // obj.dumpState();
    } else {
      ++failure;
    }
  }
  std::cout << "Total,Success,Failure,S Percentage,F Percentage" << std::endl;
  std::cout << total   << ","
            << success << ","
            << failure << ","
            << ((success/(float)total)*100) << ","
            << ((failure/(float)total)*100)
            << std::endl;
  return 0;
}
