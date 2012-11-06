// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
% g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin.c++.app
% valgrind RunDarwin.c++.app > RunDarwin.out

To configure Doxygen:
doxygen -g
That creates the file Doxyfile.
Make the following edits:
EXTRACT_ALL = YES
EXTRACT_PRIVATE = YES
EXTRACT_STATIC = YES
GENERATE_LATEX = NO

To document the program:
doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert> // assert
#include <cstdlib> // rand, srand
#include <iostream> // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"
// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----
    // food
    // ----
   Species food = Species("food");
   /*
   0: left
   1: go 0
   */
   food.addInstruction("left",-1);
   food.addInstruction("go",0);

   // ------
   // hopper
   // ------
   Species hopper = Species("hopper");
    /*
   0: hop
   1: go 0
   */
   hopper.addInstruction("hop",-1);
   hopper.addInstruction("go",0);

   // -----
   // rover
   // -----
   Species rover = Species("rover");
   /*
   0: if_enemy 9
   1: if_empty 7
   2: if_random 5
   3: left
   4: go 0
   5: right
   6: go 0
   7: hop
   8: go 0
   9: infect
   10: go 0
   */
   rover.addInstruction("if_enemy",9);
   rover.addInstruction("if_empty",7);
   rover.addInstruction("if_random",5);
   rover.addInstruction("left",-1);
   rover.addInstruction("go",0);
   rover.addInstruction("right",-1);
   rover.addInstruction("go",0);
   rover.addInstruction("hop",-1);
   rover.addInstruction("go",0);
   rover.addInstruction("infect",-1);
   rover.addInstruction("go",0);

   // ----
   // trap
   // ----
   Species trap = Species("trap");
   /*
   0: if_enemy 3
   1: left
   2: go 0
   3: infect
   4: go 0
   */
   trap.addInstruction("if_enemy",3);
   trap.addInstruction("left",-1);
   trap.addInstruction("go",0);
   trap.addInstruction("infect",-1);
   trap.addInstruction("go",0);

   // ----------
   // darwin 8x8
   // ----------

   try {
       cout << "*** Darwin 8x8 ***" << endl;
        /*
   8x8 Darwin
   Food, facing east, at (0, 0)
   Hopper, facing north, at (3, 3)
   Hopper, facing east, at (3, 4)
   Hopper, facing south, at (4, 4)
   Hopper, facing west, at (4, 3)
   Food, facing north, at (7, 7)
   Simulate 5 moves.
   Print every grid.
    */
/*   World darwin1 = World(8,8);
   Creature c1 = Creature("food1", &food, 0, 0, "east",&darwin1);
   Creature c2 = Creature("hopper1", &hopper, 3, 3, "north",&darwin1);
   Creature c3 = Creature("hopper2", &hopper, 3, 4, "east",&darwin1);
   Creature c4 = Creature("hopper3", &hopper, 4, 4, "south",&darwin1);
   Creature c5 = Creature("hopper4", &hopper, 4, 3, "west",&darwin1);
   Creature c6 = Creature("food2", &food, 7, 7, "north",&darwin1);
   darwin1.addCreature(&c1);
   darwin1.addCreature(&c2);
   darwin1.addCreature(&c3);
   darwin1.addCreature(&c4);
   darwin1.addCreature(&c5);
   darwin1.addCreature(&c6);
   darwin1.run(5);
*/   }
   catch (const invalid_argument&) {
       assert(false);}
   catch (const out_of_range&) {
       assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        /*
7x9 Darwin
Trap, facing south, at (0, 0)
Hopper, facing east, at (3, 2)
Rover, facing north, at (5, 4)
Trap, facing west, at (6, 8)
Simulate 5 moves.
Print every grid.
*/
   World darwin2 = World(7,9);
   Creature c7 = Creature("trap1", &trap, 0, 0, "south",&darwin2);
   Creature c8 = Creature("hopper5", &hopper, 3, 2, "east",&darwin2);
   Creature c9 = Creature("rover1", &rover, 5, 4, "north",&darwin2);
   Creature c10 = Creature("trap2", &trap, 6, 8, "west",&darwin2);
   darwin2.addCreature(&c7);
   darwin2.addCreature(&c8);
   darwin2.addCreature(&c9);
   darwin2.addCreature(&c10);
   darwin2.run(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        /*
Randomly place the following creatures facing randomly.
Call rand(), mod it with 5184 (72x72), and use that for the position
in a row-major order grid.
Call rand() again, mod it with 4 and use that for it's direction with
the ordering: west, north, east, south.
Do that for each kind of creature.
10 Food
10 Hopper
10 Rover
10 Trap
Simulate 1000 moves.
Print every 100th grid.
*/

   /*
   World darwin3 = World(7,9);
   Creature c11 = Creature("food3", &food, 0, 0, "east",&darwin3);
   Creature c12 = Creature("food4", &food, 0, 0, "east",&darwin3);
   Creature c13 = Creature("food5", &food, 0, 0, "east",&darwin3);
   Creature c14 = Creature("food6", &food, 0, 0, "east",&darwin3);
   Creature c15 = Creature("food7", &food, 0, 0, "east",&darwin3);
   Creature c16 = Creature("food8", &food, 0, 0, "east",&darwin3);
   Creature c17 = Creature("food9", &food, 0, 0, "east",&darwin3);
   Creature c18 = Creature("food10", &food, 0, 0, "east",&darwin3);
   Creature c19 = Creature("food11", &food, 0, 0, "east",&darwin3);
   Creature c20 = Creature("food12", &food, 0, 0, "east",&darwin3);
   Creature c21 = Creature("hopper6", &hopper, 3, 3, "north",&darwin3);
   Creature c22 = Creature("hopper7", &hopper, 3, 3, "north",&darwin3);
   Creature c23 = Creature("hopper8", &hopper, 3, 3, "north",&darwin3);
   Creature c24 = Creature("hopper9", &hopper, 3, 3, "north",&darwin3);
   Creature c25 = Creature("hopper10", &hopper, 3, 3, "north",&darwin3);
   Creature c26 = Creature("hopper11", &hopper, 3, 3, "north",&darwin3);
   Creature c27 = Creature("hopper12", &hopper, 3, 3, "north",&darwin3);
   Creature c28 = Creature("hopper13", &hopper, 3, 3, "north",&darwin3);
   Creature c29 = Creature("hopper14", &hopper, 3, 3, "north",&darwin3);
   Creature c30 = Creature("hopper15", &hopper, 3, 3, "north",&darwin3);
   Creature c31 = Creature("rover2", &rover, 5, 4, "north",&darwin3);
   Creature c32 = Creature("rover3", &rover, 5, 4, "north",&darwin3);
   Creature c33 = Creature("rover4", &rover, 5, 4, "north",&darwin3);
   Creature c34 = Creature("rover5", &rover, 5, 4, "north",&darwin3);
   Creature c35 = Creature("rover6", &rover, 5, 4, "north",&darwin3);
   Creature c36 = Creature("rover7", &rover, 5, 4, "north",&darwin3);
   Creature c37 = Creature("rover8", &rover, 5, 4, "north",&darwin3);
   Creature c38 = Creature("rover9", &rover, 5, 4, "north",&darwin3);
   Creature c39 = Creature("rover10", &rover, 5, 4, "north",&darwin3);
   Creature c40 = Creature("rover11", &rover, 5, 4, "north",&darwin3);
   Creature c41 = Creature("trap3", &trap, 6, 8, "west",&darwin3);
   Creature c42 = Creature("trap4", &trap, 6, 8, "west",&darwin3);
   Creature c43 = Creature("trap5", &trap, 6, 8, "west",&darwin3);
   Creature c44 = Creature("trap6", &trap, 6, 8, "west",&darwin3);
   Creature c45 = Creature("trap7", &trap, 6, 8, "west",&darwin3);
   Creature c46 = Creature("trap8", &trap, 6, 8, "west",&darwin3);
   Creature c47 = Creature("trap9", &trap, 6, 8, "west",&darwin3);
   Creature c48 = Creature("trap10", &trap, 6, 8, "west",&darwin3);
   Creature c49 = Creature("trap11", &trap, 6, 8, "west",&darwin3);
   Creature c50 = Creature("trap12", &trap, 6, 8, "west",&darwin3);
   darwin3.addCreature(&c11);
   darwin3.addCreature(&c12);
   darwin3.addCreature(&c13);
   darwin3.addCreature(&c14);
   darwin3.addCreature(&c15);
   darwin3.addCreature(&c16);
   darwin3.addCreature(&c17);
   darwin3.addCreature(&c18);
   darwin3.addCreature(&c19);
   darwin3.addCreature(&c20);
   darwin3.addCreature(&c21);
   darwin3.addCreature(&c22);
   darwin3.addCreature(&c23);
   darwin3.addCreature(&c24);
   darwin3.addCreature(&c25);
   darwin3.addCreature(&c26);
   darwin3.addCreature(&c27);
   darwin3.addCreature(&c28);
   darwin3.addCreature(&c29);
   darwin3.addCreature(&c30);
   darwin3.addCreature(&c31);
   darwin3.addCreature(&c32);
   darwin3.addCreature(&c33);
   darwin3.addCreature(&c34);
   darwin3.addCreature(&c35);
   darwin3.addCreature(&c36);
   darwin3.addCreature(&c37);
   darwin3.addCreature(&c38);
   darwin3.addCreature(&c39);
   darwin3.addCreature(&c40);
   darwin3.addCreature(&c41);
   darwin3.addCreature(&c42);
   darwin3.addCreature(&c43);
   darwin3.addCreature(&c44);
   darwin3.addCreature(&c45);
   darwin3.addCreature(&c46);
   darwin3.addCreature(&c47);
   darwin3.addCreature(&c48);
   darwin3.addCreature(&c49);
   darwin3.addCreature(&c50);
   darwin3.run(1000);
   */     }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        /*
Randomly place the following creatures facing randomly.
Call rand(), mod it with 5184 (72x72), and use that for the position
in a row-major order grid.
Call rand() again, mod it with 4 and use that for it's direction with
the ordering: west, north, east, south.
Do that for each kind of creature.
10 Food
10 Hopper
10 Rover
10 Trap
10 Best
Simulate 1000 moves.
Best MUST outnumber ALL other species for the bonus pts.
Print every 100th grid.
*/
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
