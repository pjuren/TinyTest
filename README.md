TinyTest
========

What is TinyTest?
-----------------

TinyTest is a light-weight unit testing framework
for C++ projects. 

The design philosophy was to keep
the code as small as possible. 


These days, the software I write is generally command-line 
applications for use in Unix-like environments. Generally
these programs are light-weight. In the usual Unix 
philosophy, the packages I write tend to contain many 
small, focused programs that can be chained together 
to achieve more advanced goals. As a result, the unit 
tests I write are generally small, and require only simple 
functionality. The vast majority of these tests simply 
run a small peice of code and check that the result 
matches some pre-computed expected value (to some 
tolerance). I generally like to include these unit tests 
with the distribution of the software I write. There 
are a couple of advantages to doing this: (1) keeping 
the tests bundled with the software project means they 
are easily updated when changes are made; (2) it means 
the distirbuton can easily be tested on the target 
platform(s) in exactly the same form that it will be 
delivered to users; and (3) users can immediately verify 
that the distribution works for them. I don't think this 
is confusing or onerous for the user because (1) they 
don't have to do it (I always make that clear); and (2) 
mostly these projects are targeted to an 
intermediate-to-advanced user base -- after all, I'm 
expecting them to be able to handle 'make install', 
so 'make test' isn't much of a stretch. 

The problem is that most unit testing frameworks are 
too heavy. They end up accounting for too great a 
percentage of the code-base in the project, and somehow 
that feels wrongs. It's like I'm distributing a unit 
testing framework with some extra functionality embedded. 
So I decided to write my own. The design philosophy was
to keep the code as small and simple as possible. As a
result, TinyTest has just two source files, and clocks in
at just a few hundred lines of code. It's functionality is
simple, but it does everything I need, and maybe everything
you need too. 

What can TinyTest do?
---------------------

TODO

How do I use TinyTest?
----------------------

TODO

Contacts and bug reports
------------------------

Philip J. Uren
philip.uren@gmail.com

If you found a bug or mistake in this project, I would like 
to know about it. Before you send me the bug report though, 
please check the following:

1. Are you using the latest version? The bug you found may already have 
   been fixed.
2. Check that your input is in the correct format and you have selected
   the correct options.
3. Please reduce your input to the smallest possible size that still 
   produces the bug; I will need your input data to reproduce the 
	 problem, and the smaller you can make it, the easier it will be 
	 for both of us.


