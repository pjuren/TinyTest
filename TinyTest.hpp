/**
 * \file  TinyTest.hpp
 * \brief This file contains most of the code for TinyTest, including the
 *        macros for test definition and condition checking, the classes for
 *        automatic test registration and the exceptions. You should include
 *        this file at the top of your test suite.
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

#ifndef TINYTEST_H
#define TINYTEST_H

// include STL stuff
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>

/******************************************************************************
 **        Classes and macros for testing conditions in test cases           **
 ******************************************************************************/

/**
 * \brief Exceptions of this type are thrown whenever a test fails.
 */
class TinyTestException : public std::exception {
public :
  /** \brief default constructor makes a TinyTestException with no message */
  TinyTestException() : msg("") {};

  /** \brief construct a TinyTestException with the given failure message */
  TinyTestException(std::string msg) : msg(msg) {};

  /** brief default destructor */
  virtual ~TinyTestException() throw() {};

  /** brief get the failure message for this TinyTestException */
  const char* what() const throw () { return msg.c_str(); }
private:
  /** brief A message containing (optionally) extra detail about what failed */
  std::string msg;
};

/**
 * \brief Test whether two variables A and B are exactly equal. Throw a
 *        TinyTestException if they aren't.
 *
 *        The types of A and B must support !=, but they need not be the same
 *        type.
 */
#define EXPECT_EQUAL(A,B)                   \
  if (A != B) throw TinyTestException()     \

/**
 * \brief Test whether two random-access containers A and B are equal. Throw a
 *        TinyTestException if they aren't.
 *
 *        This will work for any containers where .size() and random access
 *        via [] is defined (things like vector, for example). Additionally,
 *        the types in A and B must support !=, though they needn't necessarily
 *        be the same type.
 *
 *        A and B are equal if they contain the same number of items and each
 *        pairwise element comparison with != evaluates to false.
 */
#define EXPECT_EQUAL_STL_CONTAINER(A,B)                 \
  if (A.size() != B.size()) throw TinyTestException();  \
  for (size_t i = 0; i < A.size(); ++i) {               \
    if (A[i] != B[i]) throw TinyTestException();        \
  }

/**
 * \brief Test whether two random-access containers A and B contain elements
 *        that are approximately equal (within some specified tolerance).
 *        Throw a TinyTestException if they don't.
 *
 *        This will work for any containers where .size() and random access
 *        via [] is defined (things like vector, for example). Additionally,
 *        the types in A and B must support the subtraction operator resulting
 *        in a type compatible with std::fabs, though they needn't necessarily
 *        be the same type. This works well for things like doubles and floats
 *
 *        A and B are 'near equal' if they contain the same number of items and
 *        the difference between pairwise elements (evaluated by the - operator)
 *        is within the specified tolerance.
 */
#define EXPECT_NEAR_STL_CONTAINER(A,B,TOL)                              \
  if (A.size() != B.size()) throw TinyTestException();                  \
  for (size_t i = 0; i < A.size(); ++i) {                               \
    if (std::fabs(A[i] - B[i]) > TOL) throw TinyTestException();        \
  }

/**
 * \brief TODO
 */
#define EXPECT_NOT_EQUAL(A,B)               \
  if (A == B) throw TinyTestException()     \

/**
 * \brief This macro tests whether A and B are _almost_ equal. The
 *        subtraction operator must be defined, and a tolerance can be specified
 *        by the caller. Basically, this is for floating point numbers.
 */
#define EXPECT_NEAR(A,B,TOL)                                \
  if (std::fabs(A - B) > TOL) throw TinyTestException()     \

/**
 * \brief This macro tests whether A and B are _almost_ equal. The
 *        subtraction operator must be defined, and a default tolerance of
 *        1e-20 is allowed. Basically, this is for floating point numbers.
 */
#define EXPECT_NEAR_DEF(A,B)                               \
  if (std::fabs(A - B) > 1e-20) throw TinyTestException()  \

/******************************************************************************
 **       Classes for definition, and automagic detection of test cases      **
 ******************************************************************************/

/**
 * \brief This class is the base test case class. User defined test cases
 *        will extend this class (though they won't know it necessarily,
 *        since it's done automatically for them using a macro).
 */
class TestCase {
	public:
    /** \brief TODO */
  	TestCase (const std::string& testName) : testName(testName) {;}

  	/** \brief TODO */
  	virtual ~TestCase() {};

  	/** \brief TODO */
    virtual std::string getTestName() const {return testName;}

    /** \brief TODO */
    virtual void runTest() const = 0;

  private:
    /** The name of the this test case. Used for reporting pass/fail **/
    std::string testName;
};

/**
 * \brief TODO
 */
class TestSet {
public:
  /**
   * \brief TODO
   */
  static TestSet& getTestSet() {
    static TestSet* tset = new TestSet();
    return *tset;
  }

  /**
   * \brief TODO
   */
  void addTest(const TestCase* b) {
    tests.push_back(b);
    std::cout << "Discovered test: " << b->getTestName() << std::endl;
  }

  /**
   * \brief TODO
   */
  bool run() {
    bool okay = true;
    size_t maxPad = this->maxNameLength();
    for (size_t i = 0; i < tests.size(); ++i) {
      assert(tests[i]->getTestName().size() <= maxPad);
      size_t pad = maxPad - tests[i]->getTestName().size();
      std::string padding (pad, ' ');
      std::cout << tests[i]->getTestName() << " ... " << padding;
      try {
        tests[i]->runTest();
        std::cout << "[PASSED]" << std::endl;
      } catch (TinyTestException e) {
        std::cout << "[FAILED]" << std::endl;
        okay = false;
      }
    }
    return okay;
  }

private:
  /** \brief TODO **/
  std::vector<const TestCase*> tests;

  /** \brief TODO **/
  TestSet()  {;}

  /** \brief TODO **/
  ~TestSet()  {;}

  /** \brief TODO **/
  size_t maxNameLength() const {
    size_t m = 0;
    for (size_t i = 0; i < tests.size(); ++i)
      if (tests[i]->getTestName().size() > m)
        m = tests[i]->getTestName().size();
    return m;
  }
};

/**
 * \brief TODO
 */
class TestCaseAdder {
public:
  /**
   * \brief TODO
   */
  TestCaseAdder(const TestCase* b) { TestSet::getTestSet().addTest(b); }

  /**
   * \brief TODO
   */
  ~TestCaseAdder() { }
};

/******************************************************************************
 **                   Macros for test case definition                        **
 ******************************************************************************/

/**
 * \brief TODO
 */
#define TEST(NAME)                                                      \
	class NAME : public TestCase {                                      \
    public:                                                             \
    	NAME(const std::string& testName) : TestCase( testName ) { ; }  \
      virtual void runTest() const;                                     \
    private:                                                            \
      static TestCaseAdder adder;                                       \
  };                                                                    \
  TestCaseAdder NAME::adder(new NAME(#NAME));                           \
  void NAME::runTest() const

#endif
