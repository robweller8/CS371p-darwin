// -----------------------------
// Modeled after
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
//
// Modified for the purpose of CS371P Project #5
// Matthew McClure
// -----------------------------

/*
To test the program:
% ls /usr/include/cppunit/
...
HelperMacros.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin
% valgrind TestDarwin >& TestDarwin.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#undef private
#define private public

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

struct TestDarwin : CppUnit::TestFixture {
	// --------
	// testSpecies
	void testSpecies1 () {
	   Species newSpecies = Species("hopper");
           newSpecies.addInstruction("hop",-1);
           int size = newSpecies.program.size();
           CPPUNIT_ASSERT(size ==    1);
		
	}
	

	// --------
	// testWorld1
	void testWorld1 () {
           World w(2, 2);
	   w.printWorld();
	}

        // --------
	// testIsEmpty1
	void testIsEmpty1 () {
           World w(2, 2);
	   w.printWorld();
           Species newSpecies = Species("hopper");
           Creature c = Creature("hopper1", &newSpecies, 1, 0, "north", &w);
           w.addCreature(&c);
           w.printWorld();
           bool result = w.isEmpty(1,0);
           CPPUNIT_ASSERT(!result);
	}
        // --------
	// testIsEmpty2
	void testIsEmpty2 () {
           World w(2, 2);
	   w.printWorld();
           Species newSpecies = Species("hopper");
           Creature c = Creature("hopper1", &newSpecies, 1, 0, "north", &w);
           w.addCreature(&c);
           bool result = w.isEmpty(0,0);
           CPPUNIT_ASSERT(result);
	}
        // --------
	// testIsEmpty3
	void testIsEmpty3 () {
           World w(2, 2);
	   for (int i = 0; i< 2; i++)
              for (int j = 0; j < 2; j++)
                 CPPUNIT_ASSERT(w.isEmpty(i,j));
	}
	

	
	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDarwin);
	CPPUNIT_TEST(testSpecies1);
	CPPUNIT_TEST(testWorld1);
	CPPUNIT_TEST(testIsEmpty1);
	CPPUNIT_TEST(testIsEmpty2);
	CPPUNIT_TEST(testIsEmpty3);

	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);	// turn off synchronization with C I/O
	cout << "TestDarwin.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestDarwin::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}

