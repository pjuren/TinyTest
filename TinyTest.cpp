

#include <string>
#include <iostream>
#include "TinyTest.hpp"

using std::cerr;
using std::endl;

int 
main(int argc, const char* argv[]) {
	cerr << "RUNNING UNIT TESTS" << endl;
  if (!TestSet::getTestSet().run()) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

