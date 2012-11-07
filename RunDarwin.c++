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
   // ----
   // best
   // ----
   Species best = Species("best");
   /*
   0: left
   1: left
   2: if_enemy 8
   3: if_empty 6 
   4: left
   5: go 1
   6: hop
   7: go 1
   8: infect
   9: go 1
 */

   best.addInstruction("left",-1);
   best.addInstruction("if_enemy",7);
   best.addInstruction("if_empty",5);
   best.addInstruction("left",-1);
   best.addInstruction("go",1);
   best.addInstruction("hop",-1);
   best.addInstruction("go",1);
   best.addInstruction("infect",-1);
   best.addInstruction("go",1);
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
   World darwin1 = World(8,8);
   Creature c1 = Creature("food1", &food, 0, 0, 2,&darwin1);
   Creature c2 = Creature("hopper1", &hopper, 3, 3, 1,&darwin1);
   Creature c3 = Creature("hopper2", &hopper, 3, 4, 2,&darwin1);
   Creature c4 = Creature("hopper3", &hopper, 4, 4, 3,&darwin1);
   Creature c5 = Creature("hopper4", &hopper, 4, 3, 0,&darwin1);
   Creature c6 = Creature("food2", &food, 7, 7, 1,&darwin1);
   darwin1.addCreature(&c1);
   darwin1.addCreature(&c2);
   darwin1.addCreature(&c3);
   darwin1.addCreature(&c4);
   darwin1.addCreature(&c5);
   darwin1.addCreature(&c6);
   darwin1.run(5,1);
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
   World darwin2 = World(7,9);
   Creature c7 = Creature("trap1", &trap, 0, 0, 3,&darwin2);
   Creature c8 = Creature("hopper5", &hopper, 3, 2, 2,&darwin2);
   Creature c9 = Creature("rover1", &rover, 5, 4, 1,&darwin2);
   Creature c10 = Creature("trap2", &trap, 6, 8, 0,&darwin2);
   darwin2.addCreature(&c7);
   darwin2.addCreature(&c8);
   darwin2.addCreature(&c9);
   darwin2.addCreature(&c10);
   darwin2.run(5,1);
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

   
   World darwin3 = World(72,72);
   int random = rand() % 5184;
   Creature c11 = Creature("food3", &food, random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c12 = Creature("food4", &food,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c13 = Creature("food5", &food,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c14 = Creature("food6", &food,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c15 = Creature("food7", &food,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c16 = Creature("food8", &food,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c17 = Creature("food9", &food,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c18 = Creature("food10", &food,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c19 = Creature("food11", &food,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c20 = Creature("food12", &food,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c21 = Creature("hopper6", &hopper,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c22 = Creature("hopper7", &hopper,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c23 = Creature("hopper8", &hopper,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c24 = Creature("hopper9", &hopper,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c25 = Creature("hopper10", &hopper,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c26 = Creature("hopper11", &hopper,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c27 = Creature("hopper12", &hopper,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c28 = Creature("hopper13", &hopper,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c29 = Creature("hopper14", &hopper,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c30 = Creature("hopper15", &hopper,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c31 = Creature("rover2", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c32 = Creature("rover3", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c33 = Creature("rover4", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c34 = Creature("rover5", &rover, random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c35 = Creature("rover6", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c36 = Creature("rover7", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c37 = Creature("rover8", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c38 = Creature("rover9", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c39 = Creature("rover10", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c40 = Creature("rover11", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c41 = Creature("trap3", &trap,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c42 = Creature("trap4", &trap,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c43 = Creature("trap5", &trap,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c44 = Creature("trap6", &trap,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c45 = Creature("trap7", &trap,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c46 = Creature("trap8", &trap,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c47 = Creature("trap9", &trap,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c48 = Creature("trap10", &trap,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c49 = Creature("trap11", &trap, random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c50 = Creature("trap12", &trap,  random/72, random%72, rand() % 4,&darwin3);
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
   darwin3.run(1000, 100);
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
   
   World darwin4 = World(72,72);
   int random = rand() % 5184;
   Creature c11 = Creature("food3", &food, random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c12 = Creature("food4", &food,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c13 = Creature("food5", &food,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c14 = Creature("food6", &food,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c15 = Creature("food7", &food,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c16 = Creature("food8", &food,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c17 = Creature("food9", &food,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c18 = Creature("food10", &food,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c19 = Creature("food11", &food,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c20 = Creature("food12", &food,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c21 = Creature("hopper6", &hopper,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c22 = Creature("hopper7", &hopper,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c23 = Creature("hopper8", &hopper,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c24 = Creature("hopper9", &hopper,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c25 = Creature("hopper10", &hopper,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c26 = Creature("hopper11", &hopper,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c27 = Creature("hopper12", &hopper,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c28 = Creature("hopper13", &hopper,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c29 = Creature("hopper14", &hopper,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c30 = Creature("hopper15", &hopper,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c31 = Creature("rover2", &rover,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c32 = Creature("rover3", &rover,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c33 = Creature("rover4", &rover,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c34 = Creature("rover5", &rover, random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c35 = Creature("rover6", &rover,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c36 = Creature("rover7", &rover,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c37 = Creature("rover8", &rover,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c38 = Creature("rover9", &rover,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c39 = Creature("rover10", &rover,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c40 = Creature("rover11", &rover,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c41 = Creature("trap3", &trap,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c42 = Creature("trap4", &trap,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c43 = Creature("trap5", &trap,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c44 = Creature("trap6", &trap,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c45 = Creature("trap7", &trap,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c46 = Creature("trap8", &trap,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c47 = Creature("trap9", &trap,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c48 = Creature("trap10", &trap,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c49 = Creature("trap11", &trap, random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c50 = Creature("trap12", &trap,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c51 = Creature("best1", &best,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c52 = Creature("best2", &best,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c53 = Creature("best3", &best,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c54 = Creature("best4", &best,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c55 = Creature("best5", &best,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c56 = Creature("best6", &best,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c57 = Creature("best7", &best,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c58 = Creature("best8", &best,  random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c59 = Creature("best9", &best, random/72, random%72, rand() % 4,&darwin4);
   random = rand() % 5184;
   Creature c60 = Creature("best10", &best,  random/72, random%72, rand() % 4,&darwin4);
   darwin4.addCreature(&c11);
   darwin4.addCreature(&c12);
   darwin4.addCreature(&c13);
   darwin4.addCreature(&c14);
   darwin4.addCreature(&c15);
   darwin4.addCreature(&c16);
   darwin4.addCreature(&c17);
   darwin4.addCreature(&c18);
   darwin4.addCreature(&c19);
   darwin4.addCreature(&c20);
   darwin4.addCreature(&c21);
   darwin4.addCreature(&c22);
   darwin4.addCreature(&c23);
   darwin4.addCreature(&c24);
   darwin4.addCreature(&c25);
   darwin4.addCreature(&c26);
   darwin4.addCreature(&c27);
   darwin4.addCreature(&c28);
   darwin4.addCreature(&c29);
   darwin4.addCreature(&c30);
   darwin4.addCreature(&c31);
   darwin4.addCreature(&c32);
   darwin4.addCreature(&c33);
   darwin4.addCreature(&c34);
   darwin4.addCreature(&c35);
   darwin4.addCreature(&c36);
   darwin4.addCreature(&c37);
   darwin4.addCreature(&c38);
   darwin4.addCreature(&c39);
   darwin4.addCreature(&c40);
   darwin4.addCreature(&c41);
   darwin4.addCreature(&c42);
   darwin4.addCreature(&c43);
   darwin4.addCreature(&c44);
   darwin4.addCreature(&c45);
   darwin4.addCreature(&c46);
   darwin4.addCreature(&c47);
   darwin4.addCreature(&c48);
   darwin4.addCreature(&c49);
   darwin4.addCreature(&c50);
   darwin4.addCreature(&c51);
   darwin4.addCreature(&c52);
   darwin4.addCreature(&c53);
   darwin4.addCreature(&c54);
   darwin4.addCreature(&c55);
   darwin4.addCreature(&c56);
   darwin4.addCreature(&c57);
   darwin4.addCreature(&c58);
   darwin4.addCreature(&c59);
   darwin4.addCreature(&c60);
   darwin4.run(1000, 100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ----------
    // darwin 20x20
    // ----------

    try {
        cout << "*** Darwin 20x20 with corner traps ***" << endl;
        /*
20x20 Darwin
Trap, facing south, at (0, 0)
Trap, facing north, at (19, 19)
Trap, facing west, at (0, 19)
Trap, facing east, at (19, 0)
Hopper, facing north, at (10, 10)
Hopper, facing south, at (11, 10)
Hopper, facing east, at (10, 11)
Hopper, facing east, at (11, 11)
Rover, facing north, at (5, 4)
Rover, facing north, at (5, 4)
Simulate 10 moves.
Print every grid.
*/
   World darwin2 = World(20,20);
   Creature t1 = Creature("trap1", &trap, 0, 0, 3, &darwin2);
   Creature t2 = Creature("trap2", &trap, 19, 19, 1, &darwin2);
   Creature t3 = Creature("trap3", &trap, 0, 19, 0, &darwin2);
   Creature t4 = Creature("trap4", &trap, 19, 0, 2, &darwin2);
   Creature h1 = Creature("hopper1", &hopper, 10, 10, 1, &darwin2);
   Creature h2 = Creature("hopper2", &hopper, 11, 10, 3, &darwin2);
   Creature h3 = Creature("hopper3", &hopper, 10, 11, 2, &darwin2);
   Creature h4 = Creature("hopper4", &hopper, 11, 11, 2, &darwin2);
   Creature r1 = Creature("rover1", &rover, 5, 4, 3, &darwin2);
   Creature r2 = Creature("rover2", &rover, 15, 14, 1, &darwin2);
   darwin2.addCreature(&t1);
   darwin2.addCreature(&t2);
   darwin2.addCreature(&t3);
   darwin2.addCreature(&t4);
   darwin2.addCreature(&h1);
   darwin2.addCreature(&h2);
   darwin2.addCreature(&h3);
   darwin2.addCreature(&h4);
   darwin2.addCreature(&r1);
   darwin2.addCreature(&r2);
   darwin2.run(50, 10);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 20x20
    // ----------

    try {
        cout << "*** Darwin 20x20 more traps and rovers ***" << endl;
        /*
20x20 Darwin
Trap, facing south, at (0, 0)
Trap, facing north, at (19, 19)
Trap, facing west, at (0, 19)
Trap, facing east, at (19, 0)
Trap, facing south, at (5, 5)
Trap, facing north, at (15, 15)
Trap, facing west, at (5, 15)
Trap, facing east, at (15, 5)
Hopper, facing north, at (10, 10)
Hopper, facing south, at (11, 10)
Hopper, facing east, at (10, 11)
Hopper, facing east, at (11, 11)
Rover, facing north, at (5, 4)
Rover, facing north, at (5, 4)
Simulate 10 moves.
Print every grid.
*/
   World darwin2 = World(20,20);
   Creature t1 = Creature("trap1", &trap, 0, 0, 3, &darwin2);
   Creature t2 = Creature("trap2", &trap, 19, 19, 1, &darwin2);
   Creature t3 = Creature("trap3", &trap, 0, 19, 0, &darwin2);
   Creature t4 = Creature("trap4", &trap, 19, 0, 2, &darwin2);
   Creature t5 = Creature("trap5", &trap, 5, 5, 3, &darwin2);
   Creature t6 = Creature("trap6", &trap, 15, 15, 1, &darwin2);
   Creature t7 = Creature("trap7", &trap, 5, 15, 0, &darwin2);
   Creature t8 = Creature("trap8", &trap, 15, 5, 2, &darwin2);
   Creature h1 = Creature("hopper1", &hopper, 10, 10, 1, &darwin2);
   Creature h2 = Creature("hopper2", &hopper, 11, 10, 3, &darwin2);
   Creature h3 = Creature("hopper3", &hopper, 10, 11, 2, &darwin2);
   Creature h4 = Creature("hopper4", &hopper, 11, 11, 2, &darwin2);
   Creature r1 = Creature("rover1", &rover, 5, 4, 3, &darwin2);
   Creature r2 = Creature("rover2", &rover, 15, 14, 1, &darwin2);
   Creature r3 = Creature("rover3", &rover, 15, 4, 3, &darwin2);
   Creature r4 = Creature("rover4", &rover, 5, 14, 1, &darwin2);
   Creature r5 = Creature("rover5", &rover, 13, 8, 3, &darwin2);
   Creature r6 = Creature("rover6", &rover, 8, 14, 1, &darwin2);
   darwin2.addCreature(&t1);
   darwin2.addCreature(&t2);
   darwin2.addCreature(&t3);
   darwin2.addCreature(&t4);
   darwin2.addCreature(&t5);
   darwin2.addCreature(&t6);
   darwin2.addCreature(&t7);
   darwin2.addCreature(&t8);
   darwin2.addCreature(&h1);
   darwin2.addCreature(&h2);
   darwin2.addCreature(&h3);
   darwin2.addCreature(&h4);
   darwin2.addCreature(&r1);
   darwin2.addCreature(&r2);
   darwin2.addCreature(&r3);
   darwin2.addCreature(&r4);
   darwin2.addCreature(&r5);
   darwin2.addCreature(&r6);
   darwin2.run(50, 5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 50x50
    // ----------

    try {
        cout << "*** Darwin 50x50 ***" << endl;
        srand(0);
        /*
Randomly place the following creatures facing randomly.
Call rand(), mod it with 2500 (50x50), and use that for the position
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

   
   World darwin3 = World(50,50);
   int random = rand() % 2500;
   Creature c11 = Creature("food3", &food, random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c12 = Creature("food4", &food,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c13 = Creature("food5", &food,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c14 = Creature("food6", &food,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c15 = Creature("food7", &food,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c16 = Creature("food8", &food,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c17 = Creature("food9", &food,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c18 = Creature("food10", &food,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c19 = Creature("food11", &food,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c20 = Creature("food12", &food,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c21 = Creature("hopper6", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c22 = Creature("hopper7", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c23 = Creature("hopper8", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c24 = Creature("hopper9", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c25 = Creature("hopper10", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c26 = Creature("hopper11", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c27 = Creature("hopper12", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c28 = Creature("hopper13", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c29 = Creature("hopper14", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c30 = Creature("hopper15", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c31 = Creature("rover2", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c32 = Creature("rover3", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c33 = Creature("rover4", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c34 = Creature("rover5", &rover, random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c35 = Creature("rover6", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c36 = Creature("rover7", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c37 = Creature("rover8", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c38 = Creature("rover9", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c39 = Creature("rover10", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c40 = Creature("rover11", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c41 = Creature("trap3", &trap,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c42 = Creature("trap4", &trap,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c43 = Creature("trap5", &trap,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c44 = Creature("trap6", &trap,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c45 = Creature("trap7", &trap,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c46 = Creature("trap8", &trap,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c47 = Creature("trap9", &trap,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c48 = Creature("trap10", &trap,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c49 = Creature("trap11", &trap, random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c50 = Creature("trap12", &trap,  random/50, random%50, rand() % 4,&darwin3);
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
   darwin3.run(100, 10);
       }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 50x50
    // ----------

    try {
        cout << "*** Darwin 50x50 rovers vs. hoppers ***" << endl;
        srand(0);
        /*
Randomly place the following creatures facing randomly.
Call rand(), mod it with 2500 (50x50), and use that for the position
in a row-major order grid.
Call rand() again, mod it with 4 and use that for it's direction with
the ordering: west, north, east, south.
Do that for each kind of creature.
30 Hoppers
10 Rovers
Simulate 1000 moves.
Print every 100th grid.
*/

   
   World darwin3 = World(50,50);
   int random = rand() % 2500;
   Creature c11 = Creature("hopper1", &hopper, random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c12 = Creature("hopper2", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c13 = Creature("hopper3", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c14 = Creature("hopper4", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c15 = Creature("hopper5", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c16 = Creature("hopper6", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c17 = Creature("hopper7", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c18 = Creature("hopper8", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c19 = Creature("hopper9", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c20 = Creature("hopper10", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c21 = Creature("hopper11", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c22 = Creature("hopper12", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c23 = Creature("hopper13", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c24 = Creature("hopper14", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c25 = Creature("hopper15", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c26 = Creature("hopper16", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c27 = Creature("hopper17", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c28 = Creature("hopper18", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c29 = Creature("hopper19", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c30 = Creature("hopper20", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c31 = Creature("rover2", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c32 = Creature("rover3", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c33 = Creature("rover4", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c34 = Creature("rover5", &rover, random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c35 = Creature("rover6", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c36 = Creature("rover7", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c37 = Creature("rover8", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c38 = Creature("rover9", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c39 = Creature("rover10", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c40 = Creature("rover11", &rover,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c41 = Creature("hopper21", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c42 = Creature("hopper22", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c43 = Creature("hopper23", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c44 = Creature("hopper24", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c45 = Creature("hopper25", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c46 = Creature("hopper26", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c47 = Creature("hopper27", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c48 = Creature("hopper28", &hopper,  random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c49 = Creature("hopper29", &hopper, random/50, random%50, rand() % 4,&darwin3);
   random = rand() % 2500;
   Creature c50 = Creature("hopper30", &hopper,  random/50, random%50, rand() % 4,&darwin3);
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
   darwin3.run(50, 10);
       }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

   // ----------
   // darwin 8x8
   // ----------

   try {
       cout << "*** Darwin 8x8 best vs. rover 1v1 ***" << endl;
        /*
   8x8 Darwin
   1 Rover
   1 Best
   Simulate 10 moves.
   Print every grid.
    */
   World darwin1 = World(8,8);
   Creature c1 = Creature("rover1", &rover, 0, 0, 3,&darwin1);
   Creature c2 = Creature("best1", &best, 7, 7, 1,&darwin1);
   darwin1.addCreature(&c1);
   darwin1.addCreature(&c2);
   darwin1.run(10,1);
   }
   catch (const invalid_argument&) {
       assert(false);}
   catch (const out_of_range&) {
       assert(false);}

    // ----------
    // darwin 72x72
    // ----------

    try {
        cout << "*** Darwin 72x72 bests vs. rovers ***" << endl;
        srand(0);
        /*
Randomly place the following creatures facing randomly.
Call rand(), mod it with 5184 (72x72), and use that for the position
in a row-major order grid.
Call rand() again, mod it with 4 and use that for it's direction with
the ordering: west, north, east, south.
Do that for each kind of creature.
20 Rovers
20 Bests
Simulate 1000 moves.
Print every 100th grid.
*/

   
   World darwin3 = World(72,72);
   int random = rand() % 5184;
   Creature c11 = Creature("best1", &best, random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c12 = Creature("best2", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c13 = Creature("best3", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c14 = Creature("best4", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c15 = Creature("best5", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c16 = Creature("best6", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c17 = Creature("best7", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c18 = Creature("best8", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c19 = Creature("best9", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c20 = Creature("best10", &best,  random/72, random%72, rand() % 4, &darwin3);
   random = rand() % 5184;
   Creature c21 = Creature("best11", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c22 = Creature("best12", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c23 = Creature("best13", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c24 = Creature("best14", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c25 = Creature("best15", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c26 = Creature("best16", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c27 = Creature("best17", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c28 = Creature("best18", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c29 = Creature("best19", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c30 = Creature("best20", &best,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c31 = Creature("rover2", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c32 = Creature("rover3", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c33 = Creature("rover4", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c34 = Creature("rover5", &rover, random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c35 = Creature("rover6", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c36 = Creature("rover7", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c37 = Creature("rover8", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c38 = Creature("rover9", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c39 = Creature("rover10", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c40 = Creature("rover11", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c41 = Creature("rover21", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c42 = Creature("rover22", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c43 = Creature("rover23", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c44 = Creature("rover24", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c45 = Creature("rover25", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c46 = Creature("rover26", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c47 = Creature("rover27", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c48 = Creature("rover28", &rover,  random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c49 = Creature("rover29", &rover, random/72, random%72, rand() % 4,&darwin3);
   random = rand() % 5184;
   Creature c50 = Creature("rover30", &rover,  random/72, random%72, rand() % 4,&darwin3);
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
   darwin3.run(1000, 100);
       }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
