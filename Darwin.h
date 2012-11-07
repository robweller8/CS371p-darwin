#include <cstring>
#include <vector> // vector
#include <string>
#include <iostream>
using namespace std;
class World;
class Creature;
class Instruction{
   public:
      int instructionType;
      int n;
 
     Instruction (std::string name, int x){
       n = x;
       if(strcmp(name.c_str(),"hop") == 0){
          instructionType = 0;
          n = -1;}
       else if (strcmp(name.c_str(),"left") == 0){
          instructionType = 1;
          n = -1;}
       else if (strcmp(name.c_str(),"right") == 0){
          instructionType = 2;
          n = -1;}
       else if (strcmp(name.c_str(),"infect") == 0){
          instructionType = 3;
          n = -1;}
       else if (strcmp(name.c_str(),"if_empty") == 0){
          instructionType = 4;
          n = x;}
       else if (strcmp(name.c_str(),"if_wall") == 0){
          instructionType = 5;
          n = x;}
       else if (strcmp(name.c_str(),"if_random") == 0){
          instructionType = 6;
          n = x;}
       else if (strcmp(name.c_str(),"if_enemy") == 0){
          instructionType = 7;
          n = x;}
       else if (strcmp(name.c_str(),"go") == 0){
          instructionType = 8;
         }
     }
};

class Species{
   public:
      char speciesType;
      std::vector<Instruction> program;
      Species() {}
      Species(std::string name) : program(0,Instruction("",0)) {
         if(strcmp(name.c_str(),"hopper") == 0)
            speciesType = 'h';
         else if (strcmp(name.c_str(),"rover") == 0)
            speciesType = 'r';
         else if (strcmp(name.c_str(),"food") == 0)
            speciesType = 'f';
         else if (strcmp(name.c_str(),"trap") == 0)
            speciesType = 't';
         else if (strcmp(name.c_str(),"best") == 0)
            speciesType = 'b';
      }
// ----
// addInstruction
// ----

/**
* Used to add a particular instruction to a Species' program.
* @param name defines what action or control that instruction will do. 
* @param x in the case of a control instruction, tells us what line to move to, -1 for action instructions.
*/
      void addInstruction (std::string name, int n){
         Instruction instruction = Instruction(name, n);
         program.push_back(instruction);
      }  
};


class Creature{
   public:
      int creatureTurn;
      Species type;
      World* belongsTo;
      std::string name;
      int direction;
      int programCounter;
      int row;
      int column;
      
     
   public:
      Creature(std::string n, Species* species,int r,int c,int facing, World* world){
         belongsTo = world;
         type = *species;
         row = r;
         column = c;
         name = n;
         creatureTurn = 0;
         programCounter = 0;
         direction = facing;
      }
      void execute();
};


class  World{
   public:
      int worldTurn;
      int rows;
      int columns;
   private:
      std::vector< std::vector<Creature*> > _w;
   public:
      World(){}
      World(int r, int c) {
        worldTurn = 0;
        _w = std::vector< std::vector<Creature*> >(r, std::vector<Creature*>(c));
        rows = r;
        columns = c;
        for (int i = 0; i < r; i++){
            for (int j = 0; j < c; j++){
               _w[i][j] = NULL;
                
            }  
         }
      }
// ----
// addCreature
// ----

/**
* Used to add a pointer to a certain creature to our grid.
* @param creature is a pointer to the creature we are adding.
*/
      void addCreature(Creature* newCreature){
      _w[newCreature->row][newCreature->column] = newCreature;
      }
// ----
// isEmpty
// ----

/**
* Checks to see if a given spot on the grid contains a creature.
* @param row the vertical index of the spot being checked.
* @param column the horizontal column index of the spot being checked.
* @return bool .
*/
      bool isEmpty(int row, int column){
	if(row < 0 || column < 0 || row >= rows || column >= columns)
          return false;
        else if(_w[row][column] != NULL)
          return false;
	return true;
      }
// ----
// isWall
// ----

/**
* Checks to see if a an index is the edge of the grid.
* @param row the vertical index being checked.
* @param column horizontal the index being checked.
* @return bool.
*/
      bool isWall(int row, int column){
	if(row < 0 || column < 0 || row >= rows || column >= columns)
          return true;
        else 
          return false;
      }
// ----
// isEnemy
// ----

/**
* checks if a given spot contains a creature that is not of the same species of the creature checking.
* @param row the vertical index of the spot being checked
* @param column the horizontal index of the spot being checked
* @param checker the species that is checking if the spot is a different species.
* @return bool.
*/
      bool isEnemy(int row, int column, Creature* checker){
	if(row < 0 || column < 0 || row >= rows || column >= columns){
          return false;}
        if(_w[row][column] == NULL){
          return false;} 
	if(checker->type.speciesType == _w[row][column]->type.speciesType){
          return false;}
        else{
           return true;}
      }
// ----
// infect
// ----

/**
* Changes the speices of the creature being infected to the species of the creature infecting, and resets its program counter.
* @param row the vertical index of the creature being infected.
* @param column the horizontal index of the creature being infected.
* @param infector a pointer to the creature that is infecting the other creature.
*/
      void infect(int row, int column, Creature* infector){
      _w[row][column]->type = infector->type;
      _w[row][column]->programCounter = 0;
      }
// ----
// printWorld
// ----

/**
* Used to print out the current state of the word, a "." if there is no creature at that spot.
*/
      void printWorld(){
         cout << endl;
         cout << "------------------" << endl;
        cout << "World at turn: " << worldTurn << endl;
         cout << "------------------" << endl;
         for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
               if (_w[i][j] == NULL){
                  cout << ".";
               }
               else{
                  cout << _w[i][j]->type.speciesType;
               } 
            } 
            cout << endl; 
         }
         cout << "------------------" << endl;
      }
// ----
// updateLocation
// ----

/**
* Moves a creature to a new spot in the grid, used in case of a "hop", sets old location to NULL.
* @param row the vertical index where the creature used to be.
* @param column the horizontal index where the creature used to be.
* @param newrow the vertical index of where the creature will be placed.
* @param newcol the horizontal index of where the creature will be placed.
* @param creature a pointer to the creature that is being moved.
*/
      void updateLocation(int row, int col, int newrow, int newcol, Creature* creature){
	_w[newrow][newcol] = creature;
        _w[row][col] = NULL;
      }
      void run(int turns, int printEvery);
};
// ----
// execute
// ----

/**
* Used to carry out a single instruction for this creature's species' program that is pointed to by the program counter.
*/
void Creature::execute(){
   int x = type.program[programCounter].n;
   switch (type.program[programCounter].instructionType){
      case 0:{
         if(direction == 0 && belongsTo->isEmpty(row,column-1)){
            belongsTo->updateLocation(row, column, row, column-1, this);
            --column;
            ++programCounter;
         } 
         else if(direction == 1 && belongsTo->isEmpty(row-1,column)){
            belongsTo->updateLocation(row, column, row - 1, column, this);
            --row;
            ++programCounter;
         }
         else if(direction == 2 && belongsTo->isEmpty(row,column+1)){
            belongsTo->updateLocation(row, column, row, column+1, this);
            ++column;
            ++programCounter;
         } 
         else if(direction == 3 && belongsTo->isEmpty(row+1,column)){
            belongsTo->updateLocation(row, column, row+1, column, this);
            ++row;
            ++programCounter;
         } 

         ++creatureTurn;
         break;   
      }
      case 1:{
         if(direction == 0)
            direction = 3;
         else
            --direction;
         ++programCounter;
         ++creatureTurn;
         break;
      }
      case 2:{
         if(direction == 3)
            direction = 0;
         else
            ++direction;
         ++programCounter;
         ++creatureTurn;
         break;
      }
      case 3:{
         if(direction == 0){
            if(belongsTo->isEnemy(row,column-1,this)){
               belongsTo->infect(row,column-1,this);
               ++programCounter;
              }
         }
         if(direction == 1){
            if(belongsTo->isEnemy(row-1,column,this)){
               belongsTo->infect(row-1,column,this);
               ++programCounter;
            }
         }
         if(direction == 2){
            if(belongsTo->isEnemy(row,column+1,this)){
               belongsTo->infect(row,column+1,this);
               ++programCounter;
           }
         } 
         if(direction == 3){
            if(belongsTo->isEnemy(row+1,column,this)){
               belongsTo->infect(row+1,column,this);
               ++programCounter;
            }
         } 

         ++creatureTurn;
         break;
      }
      case 4:{
         if(direction == 0){
            if(belongsTo->isEmpty(row,column-1))
               programCounter= x;
            else
               ++programCounter;     
         }
         if(direction == 1){
            if(belongsTo->isEmpty(row-1,column))
               programCounter= x;
            else
               ++programCounter;
         }
         if(direction == 2){
            if(belongsTo->isEmpty(row,column+1))
               programCounter= x;
            else
               ++programCounter;
         } 
         if(direction == 3){
            if(belongsTo->isEmpty(row+1,column))
               programCounter= x;
            else
               ++programCounter;
         } 
         break;
      }
      case 5:{
         if(direction == 0){
            if(belongsTo->isWall(row,column-1))
               programCounter= x;
            else
               ++programCounter;     
         }
         if(direction == 1){
            if(belongsTo->isWall(row-1,column))
               programCounter= x;
            else
               ++programCounter;
         }
         if(direction == 2){
            if(belongsTo->isWall(row,column+1))
               programCounter= x;
            else
               ++programCounter;
         } 
         if(direction == 3){
            if(belongsTo->isWall(row+1,column))
               programCounter= x;
            else
               ++programCounter;
         } 
         break;
      }  
      case 6:{
         srand(0);
         int random = rand();
         if(random%2 == 0)
            ++programCounter;
         else
            programCounter = x;
         break;
      }
      case 7:{
         if(direction == 0){
            if(belongsTo->isEnemy(row,column-1,this))
               programCounter= x;
            else
               ++programCounter;     
         }
         if(direction == 1){
            if(belongsTo->isEnemy(row-1,column,this))
               programCounter= x;
            else
               ++programCounter;
         }
         if(direction == 2){
            if(belongsTo->isEnemy(row,column+1,this))
               programCounter= x;
            else
               ++programCounter;
         } 
         if(direction == 3){
            if(belongsTo->isEnemy(row+1,column,this)){
               programCounter= x;}
            else{
               ++programCounter;}
         } 
         break;
      }
      case 8:{
         programCounter = x;
         break;
      }
   }

}
// ----
// run
// ----

/**
* This is used to actually run the entire world, in row major order all creatures get a turn for as many turns are assigned.
* @param turns an int of the times that the world will be run, every species gets to execute this number of action instructions. 
* @param printEvery the offset of how often printWorld() will be called.
*/
void World::run(int turns, int printEvery){
   int printTime;
   printWorld();
   
   for(int i = 0; i< turns; i++){
      for (int k = 0; k < rows; k++){
         for (int j = 0; j < columns; j++){
            if(_w[k][j] != NULL){
               while(_w[k][j] != NULL && _w[k][j]->creatureTurn == worldTurn)
                  _w[k][j]->execute();             
            }    
         }  
      }
      ++worldTurn;
      printTime = worldTurn % printEvery;
      if(printTime == 0)
         printWorld();

   }
}









