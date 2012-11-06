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
	// testWorld1
	void testWorld1 () {
           World w(2, 2);
//	   w.printWorld();
	}
	// --------
	// testWorld2
	void testWorld2 () {
           World w(20, 20);
//	   w.printWorld();
	}
	// --------
	// testWorld3
	void testWorld3 () {
           World w(72, 72);
//	   w.printWorld();
	}
	// --------
	// testSpecies1/addInstruction
	void testSpecies1 () {
	   Species newSpecies = Species("hopper");
           newSpecies.addInstruction("hop",-1);
           int size = newSpecies.program.size();
           CPPUNIT_ASSERT(size == 1);
	}
	// --------
	// testSpecies2/addInstruction
	void testSpecies2 () {
	   Species newSpecies = Species("food");
           newSpecies.addInstruction("left",-1);
           newSpecies.addInstruction("right",-1);
           int size = newSpecies.program.size();
           CPPUNIT_ASSERT(size == 2);
	}
	// --------
	// testSpecies3/addInstruction
	void testSpecies3 () {
	   Species newSpecies = Species("rover");
           newSpecies.addInstruction("hop",-1);
           newSpecies.addInstruction("left",-1);
           newSpecies.addInstruction("right",-1);
           newSpecies.addInstruction("infect",-1);
           int size = newSpecies.program.size();
           CPPUNIT_ASSERT(size == 4);
	}
    // --------
	// testIsEmpty1
	void testIsEmpty1 () {
           World w(2, 2);
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
	
	// --------
	// testAddCreature1
	void testAddCreature1 () {
           World w(2, 2);
           Species newSpecies = Species("hopper");
           Creature c1 = Creature("hopper1", &newSpecies, 1, 0, "north", &w);
           w.addCreature(&c1);
           w.printWorld();
           CPPUNIT_ASSERT(!w.isEmpty(1, 0));
	}
	// --------
	// testAddCreature2
	void testAddCreature2 () {
           World w(10, 10);
           Species newSpecies = Species("hopper");
           Creature c1 = Creature("hopper1", &newSpecies, 1, 0, "north", &w);
		   Creature c2 = Creature("hopper2", &newSpecies, 1, 1, "north", &w);
		   Creature c3 = Creature("hopper3", &newSpecies, 1, 2, "north", &w);
		   Creature c4 = Creature("hopper4", &newSpecies, 1, 3, "north", &w);
		   Creature c5 = Creature("hopper5", &newSpecies, 1, 4, "north", &w);
           w.addCreature(&c1);
		   w.addCreature(&c2);
	       w.addCreature(&c3);
		   w.addCreature(&c4);
		   w.addCreature(&c5);
           w.printWorld();
		for(int i = 0; i < 5; i++)
           CPPUNIT_ASSERT(!w.isEmpty(1, i));
	}
	// --------
	// testAddCreature3
	void testAddCreature3 () {
           World w(72, 72);
           Species newSpecies = Species("hopper");
           Creature c1 = Creature("hopper1", &newSpecies, 1, 0, "north", &w);
		   Creature c2 = Creature("hopper2", &newSpecies, 1, 1, "north", &w);
		   Creature c3 = Creature("hopper3", &newSpecies, 1, 2, "north", &w);
		   Creature c4 = Creature("hopper4", &newSpecies, 1, 3, "north", &w);
		   Creature c5 = Creature("hopper5", &newSpecies, 1, 4, "north", &w);
           Creature c6 = Creature("hopper1", &newSpecies, 2, 0, "north", &w);
		   Creature c7 = Creature("hopper2", &newSpecies, 2, 1, "north", &w);
		   Creature c8 = Creature("hopper3", &newSpecies, 2, 2, "north", &w);
		   Creature c9 = Creature("hopper4", &newSpecies, 2, 3, "north", &w);
		   Creature c10 = Creature("hopper5", &newSpecies, 2, 4, "north", &w);
           Creature c11 = Creature("hopper1", &newSpecies, 3, 0, "north", &w);
		   Creature c12 = Creature("hopper2", &newSpecies, 3, 1, "north", &w);
		   Creature c13 = Creature("hopper3", &newSpecies, 3, 2, "north", &w);
		   Creature c14 = Creature("hopper4", &newSpecies, 3, 3, "north", &w);
		   Creature c15 = Creature("hopper5", &newSpecies, 3, 4, "north", &w);
           w.addCreature(&c1);
		   w.addCreature(&c2);
	       w.addCreature(&c3);
		   w.addCreature(&c4);
		   w.addCreature(&c5);
           w.addCreature(&c6);
		   w.addCreature(&c7);
	       w.addCreature(&c8);
		   w.addCreature(&c9);
		   w.addCreature(&c10);
           w.addCreature(&c11);
		   w.addCreature(&c12);
	       w.addCreature(&c13);
		   w.addCreature(&c14);
		   w.addCreature(&c15);
		for(int i = 0; i < 5; i++)
           CPPUNIT_ASSERT(!w.isEmpty(1, i));
		for(int i = 0; i < 5; i++)
           CPPUNIT_ASSERT(!w.isEmpty(2, i));
		for(int i = 0; i < 5; i++)
           CPPUNIT_ASSERT(!w.isEmpty(3, i));
	}	
    // --------
	// testUpdateLocation1
	void testUpdateLocation1() {
           World w(2, 2);
           Species newSpecies = Species("hopper");
           Creature c = Creature("hopper1", &newSpecies, 1, 0, "north", &w);
           w.addCreature(&c);
 		   w.printWorld();
           w.updateLocation(1, 0, 0, 0, &c);
 		   w.printWorld();
           bool result = w.isEmpty(0,0);
           CPPUNIT_ASSERT(!result);
	}
    // --------
	// testUpdateLocation2
	void testUpdateLocation2() {
           World w(2, 2);
           Species newSpecies = Species("hopper");
           Creature c = Creature("hopper1", &newSpecies, 0, 0, "north", &w);
           w.addCreature(&c);
 		   w.printWorld();
           w.updateLocation(0, 0, 1, 0, &c);
 		   w.printWorld();
           bool result = w.isEmpty(1,0);
           CPPUNIT_ASSERT(!result);
	}
    // --------
	// testUpdateLocation3
	void testUpdateLocation3() {
           World w(2, 2);
           Species newSpecies = Species("hopper");
           Creature c = Creature("hopper1", &newSpecies, 1, 0, "north", &w);
           w.addCreature(&c);
 		   w.printWorld();
           w.updateLocation(1, 0, 1, 1, &c);
 		   w.printWorld();
           bool result = w.isEmpty(1,1);
           CPPUNIT_ASSERT(!result);
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDarwin);
	CPPUNIT_TEST(testWorld1);
	CPPUNIT_TEST(testWorld2);
	CPPUNIT_TEST(testWorld3);
	CPPUNIT_TEST(testSpecies1);
	CPPUNIT_TEST(testIsEmpty1);
	CPPUNIT_TEST(testIsEmpty2);
	CPPUNIT_TEST(testIsEmpty3);
	CPPUNIT_TEST(testAddCreature1);
	CPPUNIT_TEST(testAddCreature2);
	CPPUNIT_TEST(testAddCreature3);
	CPPUNIT_TEST(testUpdateLocation1);
	CPPUNIT_TEST(testUpdateLocation2);
	CPPUNIT_TEST(testUpdateLocation3);
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

