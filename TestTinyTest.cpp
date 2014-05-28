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
#include <vector>

using std::cerr;
using std::endl;

/******************************************************************************
 **                     HHELPER FUNCTIONS AND CLASSES                        **
 ******************************************************************************/

/**
 * \brief An example exception that is thrown in some tests to check that
 *        exception handling macros are working properly.
 */
class SampleException : public std::exception {};

/**
 * \brief A function that throws an exception; used for testing whether
 *        exception handling macros are working properly.
 */
static void
exceptionThrower(size_t x, size_t y) {
  throw SampleException();
}

/**
 * \brief A function that does not throw an exception; used for testing whether
 *        exception handling macros are working properly.
 */
static size_t
exceptionAvoider(size_t x, size_t y) {
  return x * y;
}


/******************************************************************************
 **                                 TESTS                                    **
 ******************************************************************************/

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

/**
 * \brief Test the container equality macro on two vectors of int.
 */
TEST(testContainerEqualPass) {
  std::vector<int> one;
  std::vector<int> two;
  one.push_back(1); two.push_back(1);
  one.push_back(3); two.push_back(3);
  one.push_back(2); two.push_back(2);
  one.push_back(6); two.push_back(6);
  EXPECT_EQUAL_STL_CONTAINER(one, two);
}

/**
 * \brief Test the container equality macros fails when two vectors have
 *        different length.
 */
TEST(testContainerEqualFail) {
  // if you look at the macro, you'll see that it iterates over the length
  // of the first vector, so let's just make sure the initial test on size is
  // okay.
  std::vector<int> one;
  std::vector<int> two;
  one.push_back(1); two.push_back(1);
  one.push_back(3); two.push_back(3);
  one.push_back(2); two.push_back(2);
                    two.push_back(6);
  EXPECT_EQUAL_STL_CONTAINER(one, two);
}

/**
 * \brief Test the container equality macro fails when two vectors have the
 *        same length, but not equal contents.
 */
TEST(testContainerEqualFail2) {
  std::vector<int> one;
  std::vector<int> two;
  one.push_back(1); two.push_back(1);
  one.push_back(3); two.push_back(3);
  one.push_back(2); two.push_back(6);
  EXPECT_EQUAL_STL_CONTAINER(one, two);
}

/**
 * \brief Test the container 'near equal' macro passes with two vectors of
 *        doubles that are close to equal.
 */
TEST(testContainerNearPass) {
  std::vector<double> one;
  std::vector<double> two;
  one.push_back(1.0); two.push_back(1.001);
  one.push_back(3.0); two.push_back(2.999);
  one.push_back(2.0); two.push_back(2.000);
  one.push_back(6.0); two.push_back(5.991);
  EXPECT_NEAR_STL_CONTAINER(one, two, 0.01)
}

/**
 * \brief Test the container 'near equal' macro fails with two vectors of
 *        doubles that are close to equal, but don't meet the tolerance
 *        threshold.
 */
TEST(testContainerNearFail) {
  std::vector<double> one;
  std::vector<double> two;
  one.push_back(1.0); two.push_back(1.001);
  one.push_back(3.0); two.push_back(2.999);
  one.push_back(2.0); two.push_back(2.000);
  one.push_back(6.0); two.push_back(5.991);
  EXPECT_NEAR_STL_CONTAINER(one, two, 0.001)
}

/**
 * \brief Test the EXPECT_THROWS macro by calling a function that throws a
 *        SampleException and make sure the macros correctly recognises it.
 */
TEST(testThrowsExceptionPass) {
  EXPECT_THROWS(SampleException, exceptionThrower(5, 6));
}

/**
 * \brief Test that the EXPECT_THROWS macro correctly fails when calling a
 *        function that does not throw any exception.
 */
TEST(testThrowsExceptionFail) {
  EXPECT_THROWS(SampleException, exceptionAvoider(5,6));
}

