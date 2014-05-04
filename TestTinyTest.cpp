#include "TinyTest.hpp"
#include <iostream>

using std::cerr;
using std::endl;

TEST(myTest) {
  EXPECT_EQUAL(1,1);
  EXPECT_NOT_EQUAL(0,1);
}
