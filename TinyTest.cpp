/**
 * \file  TinyTest.cpp
 * \brief This is the driver for TinyTest. You should link this with your tests
 *        and it will discover and run all of them.
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

// STL includes
#include <string>
#include <iostream>

// TinyTest includes
#include "TinyTest.hpp"

// bring these into the global namespace
using std::cout;
using std::endl;

/**
 * \brief A main function that will run all of the tests that TinyTest has
 *        discovered in any object files that are linked with this.
 * \param argc Number of command line arguments. This is ignored.
 * \param argv Command line arguments as c-strings. This is ignored.
 */
int 
main(int argc, const char* argv[]) {
	cout << "RUNNING UNIT TESTS" << endl;
  if (!TestSet::getTestSet().run()) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

