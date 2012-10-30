
#include <vector> // vector
#include <string>
using namespace std;


class Instruction{
      std::string instructionType;
      int n;
   public:
   Instruction (char* name, int x){
     instructionType = name;
     n = x;
   }
   

/*
   void execute(char* ){
      switch (instructionType){
         case hop{
         }
         case left{
         }
         case right{
         }
         case infect{
         }
         case if_empty{
         }
         case if_wall{
         }  
         case if_random{
         }
         case if_enemy{
         }
         case go{
         }
      }

   }
*/
};

class Species{
   std::string type;
   std::vector<Instruction> program;

      Species(std::string name) {
         type = name;
      }
   void addInstruction (char* name, int n){
      Instruction instruction = Instruction(name, n);
      program.push_back(instruction);
   }
   
   
};
class Creature{
   int direction;
   int programCounter;
   int row;
   int column;
   Creature(std::string name, Species* species){
     Species type = *species;
   }
};
class  World{
   int turn;
   int rows;
   int columns;
   std::vector< std::vector<Creature*> > _m;
   World(int r, int c) {
     _m = vector< std::vector<Creature*> >(r, std::vector<Creature*>(c));
   }

   // define index operator

  
   
};


