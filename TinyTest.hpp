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
#include <sstream>
#include <cassert>
#include <cmath>

/******************************************************************************
 **                               CONSTANTS                                  **
 *****************************************************************************/
 namespace TinyTest {
   static const double DEF_TOLERANCE = 1e-20;
 }

/******************************************************************************
 **                            HELPER FUNCTIONS                              **
 ******************************************************************************/
namespace TinyTest {
  template<typename T>
  std::string vecToString(std::vector<T> t) {
    std::stringstream ss;
    for (size_t i = 0; i < t.size(); ++i) {
      if (i != 0) ss << ", ";
      ss << t[i];
    }
    return ss.str();
  }
}

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

  /** \brief default destructor */
  virtual ~TinyTestException() throw() {};

  /** \brief get the failure message for this TinyTestException */
  const char* what() const throw () { return msg.c_str(); }
private:
  /** \brief A message containing (optionally) extra detail about what failed */
  std::string msg;
};

/**
 * \brief Test whether two variables A and B are exactly equal. Throw a
 *        TinyTestException if they aren't.
 *
 *        The types of A and B must support !=, but they need not be the same
 *        type.
 */
#define EXPECT_EQUAL(A,B)                                             \
  if (A != B) {                                                       \
    std::stringstream ss;                                             \
    ss << "EXPECT_EQUAL failed on comparison of "                     \
       << A << " and " << B;                                          \
    throw TinyTestException(ss.str());                                \
  }

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
#define EXPECT_EQUAL_STL_CONTAINER(A,B)                               \
  if (A.size() != B.size()) {                                         \
    std::stringstream ss;                                             \
    ss << "EXPECT_EQUAL_STL_CONTAINER failed on"                      \
       << "comparison of " << TinyTest::vecToString(A)                \
       << " and " << TinyTest::vecToString(B) << ". "                 \
       << "Unequal sizes.";                                           \
    throw TinyTestException(ss.str());                                \
  }                                                                   \
  for (size_t i = 0; i < A.size(); ++i) {                             \
    if (A[i] != B[i]) {                                               \
      std::stringstream ss;                                           \
      ss << "EXPECT_EQUAL_STL_CONTAINER failed on "                   \
         << "comparison of " << A[i]                                  \
         << " and " << B[i] << ". Full container "                    \
         << "contents: " << TinyTest::vecToString(A)                  \
         << " and " << TinyTest::vecToString(B);                      \
      throw TinyTestException(ss.str());                              \
    }                                                                 \
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
#define EXPECT_NEAR_STL_CONTAINER(A,B,TOL)                            \
  if (A.size() != B.size()) {                                         \
    std::stringstream ss;                                             \
    ss << "EXPECT_NEAR_STL_CONTAINER failed on "                      \
       << "comparison of " << TinyTest::vecToString(A)                \
       << " and " <<  TinyTest::vecToString(B) << ". "                \
       << "Unequal sizes.";                                           \
    throw TinyTestException(ss.str());                                \
  }                                                                   \
  for (size_t i = 0; i < A.size(); ++i) {                             \
    if (std::fabs(A[i] - B[i]) > TOL) throw TinyTestException();      \
  }

/**
 * \brief This macros tests whether A and B are _NOT_ equal. The equality
 *        operator must be defined for A and B, but they need not be the
 *        same type.
 */
#define EXPECT_NOT_EQUAL(A,B)                                         \
  if (A == B) {                                                       \
    std::stringstream ss;                                             \
    ss << "EXPECT_NOT_EQUAL failed on comparison of "                 \
       << A << " and " << B;                                          \
    throw TinyTestException(ss.str());                                \
  }

/**
 * \brief This macro tests whether A and B are _almost_ equal. The
 *        subtraction operator must be defined, and a tolerance can be specified
 *        by the caller. Basically, this is for floating point numbers.
 */
#define EXPECT_NEAR(A,B,TOL)                                          \
  if (std::fabs(A - B) > TOL) {                                       \
    std::stringstream ss;                                             \
    ss << "EXPECT_NEAR failed on comparison of "                      \
       << A << " and " << B                                           \
       << " with tolerance of " << TOL;                               \
    throw TinyTestException(ss.str());                                \
  }

/**
 * \brief This macro tests whether A and B are _almost_ equal. The
 *        subtraction operator must be defined, and a default tolerance of
 *        1e-20 is allowed. Basically, this is for floating point numbers.
 */
#define EXPECT_NEAR_DEF(A,B)                                          \
  if (std::fabs(A - B) > TinyTest::DEF_TOLERANCE) {                   \
    std::stringstream ss;                                             \
    ss << "EXPECT_NEAR_DEF failed on comparison of "                  \
       << A << " and " << B                                           \
       << " with tolerance of " << TinyTest::DEF_TOLERANCE;           \
    throw TinyTestException(ss.str());                                \
  }

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
    /** \brief Construct a new test case with the given name
     *  \param testName name of the test case
     */
  	TestCase (const std::string& testName) : testName(testName) {;}

  	/** \brief Test case destructor */
  	virtual ~TestCase() {};

  	/** \brief Get the name of this test case */
    virtual std::string getTestName() const {return testName;}

    /** \brief Run the code for this test. If this method completes without
     *         throwing any exceptions the test is considered to have passed.
     */
    virtual void runTest() const = 0;

  private:
    /** The name of the this test case. Used for reporting pass/fail **/
    std::string testName;
};

/**
 * \brief This class defines a Test Set, which is really just a collection of
 *        test cases. Uses the factory pattern; objects of this class should
 *        not be directly constructed. When one is needed, call getTestSet().
 */
class TestSet {
public:
  /**
   * \brief get a reference to a test set; at present, we maintain only one
   *        test set. On the first call, it is constructed. Every subsequent
   *        call just returns a reference to the same set.
   */
  static TestSet& getTestSet() {
    static TestSet* tset = new TestSet();
    return *tset;
  }

  /**
   * \brief add a test case to this test set.
   */
  void addTest(const TestCase* b) {
    tests.push_back(b);
    std::cout << "Discovered test: " << b->getTestName() << std::endl;
  }

  /**
   * \brief run all of the test cases in this test set and output their
   *        name and success/failure to stderr.
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
        if (std::string(e.what()).empty())
          std::cout << "[FAILED] [Reason: UNKNOWN]" << std::endl;
        else
          std::cout << "[FAILED] [Reason: " << e.what() << "]" << std::endl;
        okay = false;
      }
    }
    return okay;
  }

private:
  /** collection of test cases in this test set; store as pointers to allows
   *  run-time polymorphism; user-defined test cases extend TestCase.
   */
  std::vector<const TestCase*> tests;

  /** \brief make the constructor private; this is a factory class, so we
   *         disallow construction from outside.
   */
  TestSet()  {;}

  /** \brief make the destructor private */
  ~TestSet()  {;}

  /** \brief what is the length of the name of the test with the longest name */
  size_t maxNameLength() const {
    size_t m = 0;
    for (size_t i = 0; i < tests.size(); ++i)
      if (tests[i]->getTestName().size() > m)
        m = tests[i]->getTestName().size();
    return m;
  }
};

/**
 * \brief This is a helper class that facilitates automatic registration of
 *        tests. When one of these is constructed, it is given a TestSet
 *        pointer (in reality, a pointer to an object that is a subclass of
 *        TestSet), which it registers with a static test set maintained by
 *        the TestSet class.
 */
class TestCaseAdder {
public:
  /**
   * \brief construct a TestCaseAdder; just register the test case with
   *        a test set; note that TestSet::getTestSet() returns a static
   *        test set, so these are always registered with the same test
   *        at the moment.
   */
  TestCaseAdder(const TestCase* b) { TestSet::getTestSet().addTest(b); }

  /**
   * \brief destructor; nothing to do here really.
   */
  ~TestCaseAdder() { }
};

/******************************************************************************
 **                   Macros for test case definition                        **
 ******************************************************************************/

/**
 * \brief This is the macro that users will employ to define their tests. Each
 *        test they define is a sub-class of TestCase. We use a little trick
 *        here to do automatic test registration. The class has a static member
 *        of TestCaseAdder, which we initialise when the macro is expanded,
 *        passing to it an object constructed from the newly defined test case
 *        class. The TestCaseAdder then just registers this object with a
 *        static test set maintained by the TestSet class.
 */
#define TEST(NAME)                                                      \
  class NAME : public TestCase {                                        \
    public:                                                             \
      NAME(const std::string& testName) : TestCase( testName ) { ; }    \
      virtual void runTest() const;                                     \
    private:                                                            \
      static TestCaseAdder adder;                                       \
  };                                                                    \
  TestCaseAdder NAME::adder(new NAME(#NAME));                           \
  void NAME::runTest() const

#endif
