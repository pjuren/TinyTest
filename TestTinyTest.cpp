#include "TinyTest.hpp"
#include <iostream>

using std::cerr;
using std::endl;

TEST(testEqualityMacroSuccess) {
  // this should pass
  EXPECT_EQUAL(1,1);
}

TEST(testInequalityMacroSuccess) {
  // this should pass
  EXPECT_NOT_EQUAL(0,1);
}

TEST(testNearSuccess) {
  // this should pass, as the default tolerance is 1e-20
  EXPECT_NEAR_DEF(0, 1e-20);
}

TEST(testNearDefTolSuccess) {
  // this should pass; although the difference doesn't meet
  // the default tolerance, we have lowered that threshold.
  EXPECT_NEAR(0, 0.0001, 0.001);
}

TEST(testEqualityMacroFail) {
  // this should fail
  EXPECT_EQUAL(0,1);
}

TEST(testInequalityMacroFail) {
  // this should fail
  EXPECT_NOT_EQUAL(1,1);
}

TEST(testNearFail) {
  // this should fail as the difference exceed the
  // default tolerance of 1e-20
  EXPECT_NEAR_DEF(0, 0.0001);
}

TEST(testNearTolFail) {
  // this should fail; it would have passed at the default
  // the default tolerance of 1e-20, but it should fail here
  // because increase that threshold
  EXPECT_NEAR(0, 1e-30, 1e-31);
}
