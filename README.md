TinyTest V0.1b
==============

What is TinyTest?
-----------------

TinyTest is a light-weight unit testing framework for C++ projects. 

These days, the software I write is generally command-line applications for use
in Unix-like environments. Generally these programs are light-weight. In the 
usual Unix philosophy, the packages I write tend to contain many small, focused 
programs that can be chained together to achieve more advanced goals. As a 
result, the unit tests I write are generally small, and require only simple 
functionality. The vast majority of these tests simply run a small peice of 
code and check that the result matches some pre-computed expected value (to some 
tolerance). I generally like to include these unit tests with the distribution 
of the software I write. There are a couple of advantages to doing this: (1) 
keeping the tests bundled with the software project means they are easily 
updated when changes are made; (2) it means the distirbuton can easily be 
tested on the target platform(s) in exactly the same form that it will be 
delivered to users; and (3) users can immediately verify that the distribution 
works for them. I don't think this is confusing or onerous for the user because 
(1) they don't have to do it (I always make that clear); and (2) mostly these 
projects are targeted to an intermediate-to-advanced user base -- after all, I'm 
expecting them to be able to handle 'make install', so 'make test' isn't much 
of a stretch. 

The problem with all this is that most unit testing frameworks are too heavy. 
They end up accounting for too great a percentage of the code-base in the 
project, and somehow that feels wrong. It's like I'm distributing a unit 
testing framework with some extra functionality embedded. So I decided to write 
my own. The design philosophy was to keep the code as small and simple as 
possible. As a result, TinyTest clocks in at just a few hundred lines of code. 
It's functionality is simple, but it does everything I need, and maybe 
everything you need too. 

What can TinyTest do?
---------------------

I based TinyTest on my use of Google Test, so I've tried to reproduce the 
features of that package that I liked. This initial release contains just the 
basics. More may come later as and when I find it useful to add them. TinyTest 
supports automatic test detection. You don't need to register any tests, as 
long as you use the included macros to define the tests (see below).

TinyTest also contains a set of macros for testing the values computed by 
your unit tests. This release contains the following macros:

**EXPECT_EQUAL(A,B)**        Test whether two values are exactly identical. 
                             Typical usage would be 
                             EXPECT_EQUAL(someFunction(), 5), where 
                             someFunction computes a value (integer, probably) 
                             and you expect it to compute the value 5 on this 
                             call.
                             
**EXPECT_NOT_EQUAL(A,B)**    Same as EXPECT_EQUAL really, except that it fails 
                             if the values are exactly equal and passes if they 
                             are not.

**EXPECT_NEAR(A,B,TOL)**     Useful for comparing floating point numbers,
                             where A and B are considered equal if the 
                             difference between them does not exceed TOL.

**EXPECT_NEAR(A,B)**         Same as EXPECT_NEAR(A,B,TOL), but with a default 
                             value for TOL (presently 1e-20; in future I may 
                             provide a mechanism for changing this, but for 
                             now it is fixed). 

How do I use TinyTest?
----------------------

It's pretty easy. All you need to do is include the files TinyTest.cpp and 
TinyTest.hpp in your project (usually I just include the whole directory,
but really just those two files are needed). To write a test set, you make 
a file something like myTests.cpp. In this, you must #include TinyTest.hpp
(and whatever else you need to run your code). Then you write your tests like
this (in myTests.cpp):

    TEST(myTest) {
      // whatever code you need here for your test
  
      // check the compute values match what you expect
      EXPECT_EQUAL(1,1);
      EXPECT_NOT_EQUAL(0,1);
    }

You define as many of these as you want. You don't need any other code, 
TinyTest will automatically find your tests, run each one and print the 
result (pass or fail) to stdout. 

To build your test do something like this:

> g++ -o myTests myTests.cpp /path/to/TinyTest/TinyTest.cpp -I/path/to/TinyTest/

Now run your tests like this

> ./myNewTest

I tend to automate this process in my projects by adding it to the Makefile as 
the target 'test'. If you want an example, take a look at the file 
TestTinyTest.cpp included in the distribution. This just runs a set of simple
tests using TinyTest, some of which are expected to pass, some of which are
expeted to fail. In the included Makefile, I build and run these tests then 
compare the output to what I expect (when 'make test' is execute). Actually, 
that's a regression test, you would normally only include tests you expect to 
pass, but since I wanted to check that tests fail when they should, I have 
done so here. It's still a good example of how to write and compile a simple 
test suite.  

Contacts and bug reports
------------------------

Philip J. Uren
philip.uren@gmail.com

If you found a bug or mistake in this project, I would like 
to know about it. Before you send me the bug report though, 
please check the following:

1. Are you using the latest version? The bug you found may already have been 
   fixed.
2. Check that your input is in the correct format and you have selected
   the correct options.
3. Please reduce your input to the smallest possible size that still 
   produces the bug; I will need your input data to reproduce the 
	 problem, and the smaller you can make it, the easier it will be 
	 for both of us.

