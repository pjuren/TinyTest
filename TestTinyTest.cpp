#include "TinyTest.hpp"
#include <iostream>

using std::cerr;
using std::endl;

TEST(testEqualityMacro) {
  // this should pass
  EXPECT_EQUAL(1,1);
}

TEST(testInequalityMacro) {
  // this should pass
  EXPECT_NOT_EQUAL(0,1);
}

TEST(testEqualityMacroFail) {
  // this should fail
  EXPECT_EQUAL(0,1);
}

TEST(testInequalityMacroFail) {
  // this should fail
  EXPECT_NOT_EQUAL(1,1);
}
