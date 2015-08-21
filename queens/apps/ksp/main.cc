#include <iostream>
#include "src/Ksp.h"
#include "src/include/util.h"

#define DEFAULT_NUM_OF_PLAYERS 9

int
main(int argc, char *argv[])
{

  if (argc > 2) {
    std::cerr << "Usage   : " << argv[0] << " [num_of_players]" << std::endl;
    std::cerr << "Options : " << std::endl;
    std::cerr << "          [num_of_players] : <unsigned> (default = 9)" << std::endl;
    exit(1);
  }

  unsigned int num_of_players = DEFAULT_NUM_OF_PLAYERS;

  if (argc == 2) {
    if (utility::getUnsignedFromString(argv[1], num_of_players)) {
      std::cerr << "Error: invalid value '" << argv[1] << "' specified for <num_of_players>" << std::endl;
      exit(1);
    }
  }

  Ksp kObj(num_of_players);

  std::cout << "---------------------------------------------------------------------------" << std::endl;
  std::cout << "Solving the KSP problem for number of players = " << num_of_players << std:: endl;
  std::cout << "---------------------------------------------------------------------------" << std::endl;
  
  bool success = false;
  success = kObj.solve();

  std::cout << "---------------------------------------------------------------------------" << std::endl;
  if (success) {
    std::cout << "Goal was reached" << std::endl;
  } else {
    std::cout << "Goal was not reached" << std::endl;
  }

  return 0;
}
