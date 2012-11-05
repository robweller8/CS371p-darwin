#include <cstring>
#include <vector> // vector
#include <string>
using namespace std;
class World;
class Creature;
class Instruction{
   public:
      int instructionType;
      int n;
 
     Instruction (char* name, int x){
       if(strcmp(name,"hop") == 0)
          instructionType = 0;
       else if (strcmp(name,"left") == 0)
          instructionType = 1;
       else if (strcmp(name,"right") == 0)
          instructionType = 2;
       else if (strcmp(name,"infect") == 0)
          instructionType = 3;
       else if (strcmp(name,"if_empty") == 0)
          instructionType = 4;
       else if (strcmp(name,"if_wall") == 0)
          instructionType = 5;
       else if (strcmp(name,"if_random") == 0)
          instructionType = 6;
       else if (strcmp(name,"if_enemy") == 0)
          instructionType = 7;
       else if (strcmp(name,"go") == 0)
          instructionType = 8;
       n = x;
     }
};

class Species{
   public:
      std::string type;
      std::vector<Instruction> program;
      Species() {}
      Species(std::string name) {
         type = name;
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
     Creature(std::string n, Species* species,int row,int column,int direction, World* world){
       belongsTo = world;
       type = *species;
       name = n;
       
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
      }
      void addCreature(std::string name, Species* species, int row, int column, int direction){
         Creature newCreature = Creature(name, species, row, column, direction, this);
         _w[row][column] = &newCreature;
      }
      bool isEmpty(int row, int column){
	if(row < 0 || column < 0 || row >= rows || column >= columns)
          return false;
        else if(_w[row][column] != NULL)
          return false;
	return true;
      }
      void updateLocation(int row, int col, int newrow, int newcol, Creature* creature){
	_w[newrow][newcol] = creature;
        _w[row][col] = NULL;
      }
};

void Creature::execute(Instruction* instructionToExecute){
   switch ((*instructionToExecute).instructionType){
      case 0:{
         if(direction = 0 && belongsTo->isEmpty(row+1,column)){
            belongsTo->updateLocation(row, column, row + 1, column, this);
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

