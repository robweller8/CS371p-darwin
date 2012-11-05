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
 
     Instruction (char* name, int x){
       if(strcmp(name,"hop") == 0){
          instructionType = 0;
          n = -1;}
       else if (strcmp(name,"left") == 0){
          instructionType = 1;
          n = -1;}
       else if (strcmp(name,"right") == 0){
          instructionType = 2;
          n = -1;}
       else if (strcmp(name,"infect") == 0){
          instructionType = 3;
          n = -1;}
       else if (strcmp(name,"if_empty") == 0){
          instructionType = 4;
          n = x;}
       else if (strcmp(name,"if_wall") == 0){
          instructionType = 5;
          n = x;}
       else if (strcmp(name,"if_random") == 0){
          instructionType = 6;
          n = x;}
       else if (strcmp(name,"if_enemy") == 0){
          instructionType = 7;
          n = x;}
       else if (strcmp(name,"go") == 0){
          instructionType = 8;
          n = x;}
     }
};

class Species{
   public:
      std::string name;
      std::vector<Instruction> program;
      Species() {}
      Species(char* name) {
         if(strcmp(name,"hopper") == 0)
            name = "h";
         else if (strcmp(name,"rover") == 0)
            name = "r";
         else if (strcmp(name,"food") == 0)
            name = "f";
         else if (strcmp(name,"trap") == 0)
            name = "t";
         else if (strcmp(name,"best") == 0)
            name = "b";
      }
      void addInstruction (char* name, int n){
         Instruction instruction = Instruction(name, n);
         program.push_back(instruction);
      }  
};


class Creature{
   public:
      int creatureTurn;
      Species type;
      World* belongsTo;
   private:
      int direction;
      int programCounter;
      int row;
      int column;
      std::string name;
     
   public:
      Creature(std::string n, Species* species,int row,int column,char* facing, World* world){
         belongsTo = world;
         type = *species;
         name = n;
         if(strcmp(facing,"north") == 0)
            direction = 0;
         else if (strcmp(facing,"east") == 0)
            direction = 1;
         else if (strcmp(facing,"south") == 0)
            direction = 2;
         else if (strcmp(facing,"west") == 0)
            direction = 3;
      }
      void execute(Instruction* instructionToExecute);
};


class  World{
   public:
      int turn;
      int rows;
      int columns;
   private:
      std::vector< std::vector<Creature*> > _w;
   public:
      World(){}
      World(int r, int c) {
        _w = vector< std::vector<Creature*> >(r, std::vector<Creature*>(c));
        rows = r;
        columns = c;
        for (int i = 0; i < r; i++){
            for (int j = 0; j < c; j++){
               _w[i][j] = 0;
                
            }  
         }
      }
      void addCreature(std::string name, Species* species, int row, int column, char* direction){
         Creature newCreature = Creature(name, species, row, column, direction, this);
         _w[row][column] = &newCreature;
      }

      bool isEmpty(int row, int column){
	if(row < 0 || column < 0 || row >= rows || column >= columns)
          return false;
        else if(_w[row][column] != 0)
          return false;
	return true;
      }

      void printWorld(){
         cout << endl;
         cout << "------------------" << endl;
        // cout << "World at turn: " << turn << endl;
         cout << "------------------" << endl;
         for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
               if (_w[i][j] == 0){
                  cout << " 0 ";
               }
               else{
                  cout << (*(_w[i][j])).type.name;
               } 
            } 
            cout << endl; 
         }
         cout << "------------------" << endl;
      }
      void updateLocation(int row, int col, int newrow, int newcol, Creature* creature){
	_w[newrow][newcol] = creature;
        _w[row][col] = 0;
      }
      void run(int turns);
};

void Creature::execute(Instruction* instructionToExecute){
   switch ((*instructionToExecute).instructionType){
      case 0:{
         if(direction == 0 && belongsTo->isEmpty(row+1,column)){
            belongsTo->updateLocation(row, column, row + 1, column, this);
            row++;
         }
         if(direction == 1 && belongsTo->isEmpty(row,column+1)){
            belongsTo->updateLocation(row, column, row, column+1, this);
            row++;
         } 
         if(direction == 2 && belongsTo->isEmpty(row-1,column)){
            belongsTo->updateLocation(row, column, row - 1, column, this);
            row++;
         } 
         if(direction == 3 && belongsTo->isEmpty(row,column-1)){
            belongsTo->updateLocation(row, column, row, column-1, this);
            row++;
         }    
      }
      case 1:{
      }
      case 2:{
      }
      case 3:{
      }
      case 4:{
      }
      case 5:{
      }  
      case 6:{
      }
      case 7:{
      }
      case 8:{
      }
   }

}
void World::run(int turns){
}

