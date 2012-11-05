// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
% g++ -pedantic -std=c++0x -Wall RunCollatz.c++ -o RunCollatz.c++.app
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
   rover.addInstruction("if_enemy",9)
   rover.addInstruction("if_empty",7)
   rover.addInstruction("if_random",5)
   rover.addInstruction("left",-1)
   rover.addInstruction("go",0)
   rover.addInstruction("right",-1)
   rover.addInstruction("go",0)
   rover.addInstruction("hop",-1)
   rover.addInstruction("go",0)
   rover.addInstruction("infect",-1)
   rover.addInstruction("go",0)

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
addCreature(std::string name, Species* species, int row, int column, char* direction){
*/
   World darwin1 = World(8,8);
   darwin1.addCreature("food1", &food, 0, 0, "east");
   darwin1.addCreature("hopper1", &hopper, 3, 3, "north");
   darwin1.addCreature("hopper2", &hopper, 3, 4, "east");
   darwin1.addCreature("hopper3", &hopper, 4, 4, "south");
   darwin1.addCreature("hopper4", &hopper, 4, 3, "west");
   darwin1.addCreature("food2", &food, 7, 7, "north");
   }
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
        }
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
