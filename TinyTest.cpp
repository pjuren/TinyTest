

#include <string>
#include <iostream>
#include "TinyTest.hpp"

using std::cerr;
using std::endl;

int 
main(int argc, const char* argv[]) {
	cerr << "running tests " << endl;
  TestSet::getTestSet().run();
}

