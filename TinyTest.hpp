/**
 * TinyTest
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
 * \brief TODO
 */
class TinyTestException : public std::exception {
public :
  TinyTestException() : msg("") {};
  TinyTestException(std::string msg) : msg(msg) {};
  virtual ~TinyTestException() throw() {};
  const char* what() const throw () { return msg.c_str(); }
private:
  std::string msg;
};

/**
 * \brief TODO
 */
#define EXPECT_EQUAL(A,B)                   \
  if (A != B) throw TinyTestException()     \

/**
 * \brief TODO
 */
#define EXPECT_NOT_EQUAL(A,B)               \
  if (A == B) throw TinyTestException()     \

/**
 * \brief TODO
 */
#define EXPECT_NEAR(A,B,TOL)                                \
  if (std::fabs(A - B) > TOL) throw TinyTestException()     \

/**
 * \brief TODO
 */
#define EXPECT_NEAR_DEF(A,B)                               \
  if (std::fabs(A - B) > 1e-20) throw TinyTestException()  \

/******************************************************************************
 **       Classes for definition, and automagic detection of test cases      **
 ******************************************************************************/

/**
 * \brief TODO
 */
class TestCase {
	public:
  	TestCase (const std::string& testName) : testName(testName) {;}
  	virtual ~TestCase() {};

    virtual std::string getTestName() const {return testName;}
    virtual void runTest() const = 0;

  private:
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
		std::vector<const TestCase*> tests;
  	TestSet()  {;}
    ~TestSet()  {;}
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
  	TestCaseAdder(const TestCase* b) {
    	TestSet::getTestSet().addTest(b);
   	}

    ~TestCaseAdder() { }
};

/******************************************************************************
 **                   Macros for test case definition                        **
 ******************************************************************************/

#define TEST(NAME)                                                    \
	class NAME : public TestCase {                                      \
    public:                                                           \
    	NAME(const std::string& testName) : TestCase( testName ) { ; }  \
      virtual void runTest() const;                                   \
    private:                                                          \
      static TestCaseAdder adder;                                     \
  };                                                                  \
  TestCaseAdder NAME::adder(new NAME(#NAME));                         \
  void NAME::runTest() const

