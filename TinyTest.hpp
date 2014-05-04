#include <iostream>
#include <string>
#include <vector>

/******************************************************************************
 **       Classes for definition, and automagic detection of test cases      **
 ******************************************************************************/

/**
 * \brief TODO
 */
class TestCase {
	public:
  	TestCase (const std::string& testName) : testName(testName) {;}
  	virtual ~TestCase();

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
		static TestSet& getTestSet() {
    	static TestSet* tset = new TestSet();
      return *tset;
    }

    void addTest(const TestCase* b) {
			tests.push_back(b);
    	std::cout << "adding test " << b->getTestName() << std::endl;
    }

		void run() {
			for (size_t i = 0; i < tests.size(); ++i) {
				tests[i]->runTest();
			}
		}

	private:
		std::vector<const TestCase*> tests;
  	TestSet()  {;}
    ~TestSet()  {;}
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

/******************************************************************************
 **               Macros for testing conditions in test cases                **
 ******************************************************************************/

