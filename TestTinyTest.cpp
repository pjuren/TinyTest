/**
 * \file  TestTinyTest.cpp
 * \brief This file defines a set of standard tests to run on the comparison
 *        macros that come with TinyTest, some of which are expected to
 *        succeed and some of which are expected to fail. The results can be
 *        compared against the file regressionTestExpectedOutput.txt using
 *        diff; this is a rudimentary regression test and is implemented in
 *        the included make file as the target 'test'
 *
 * \authors Philip J. Uren
 *
 * \section copyright Copyright Details
 * Copyright (C) 2014 Philip J. Uren
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
**/

#include "TinyTest.hpp"
#include <iostream>

using std::cerr;
using std::endl;

/**
 * \brief Test that the equality macro produces a pass in a simple situation
 *        where it should.
 */
TEST(testEqualityMacroSuccess) {
  EXPECT_EQUAL(1,1);
}

/**
 * \brief Test that the inequality macro produces a pass in a simple situation
 *        where it should.
 */
TEST(testInequalityMacroSuccess) {
  EXPECT_NOT_EQUAL(0,1);
}

/**
 * \brief Test that the macro for comparing floating point values that are
 *        essentially equal produces a pass when presented with a difference
 *        that is smaller than the default tolerance.
 */
TEST(testNearSuccess) {
  // this should pass, as the default tolerance is 1e-20
  EXPECT_NEAR_DEF(0, 1e-20);
}

/**
 * \brief Test that the macro for comparing floating point values that are
 *        essentially equal produces a pass when presented with a difference
 *        that is smaller than a specified tolerance (but greater than the
 *        default tolerance).
 */
TEST(testNearDefTolSuccess) {
  // this should pass; although the difference doesn't meet
  // the default tolerance, we have lowered that threshold.
  EXPECT_NEAR(0, 0.0001, 0.001);
}

/**
 * \brief Test that the equality macro fails when presented with two values
 *        that are not equal.
 */
TEST(testEqualityMacroFail) {
  // this should fail
  EXPECT_EQUAL(0,1);
}

/**
 * \brief Test that the inequality macros produces a fail when presented with
 *        two objects that are equal.
 */
TEST(testInequalityMacroFail) {
  // this should fail
  EXPECT_NOT_EQUAL(1,1);
}

/**
 * \brief Test that the macro for comparing floating point values that are
 *        essentially the same fails when presented with two values that differ
 *        by more than the default tolerance.
 */
TEST(testNearFail) {
  // this should fail as the difference exceed the
  // default tolerance of 1e-20
  EXPECT_NEAR_DEF(0, 0.0001);
}

/**
 * \brief Test that the macro for comparing floating point values that are
 *        essentially equal fails when presented with two values that differ
 *        by a value greater than a specified threshold (but less than the
 *        default tolerance).
 */
TEST(testNearTolFail) {
  // this should fail; it would have passed at the default
  // the default tolerance of 1e-20, but it should fail here
  // because increase that threshold
  EXPECT_NEAR(0, 1e-30, 1e-31);
}
