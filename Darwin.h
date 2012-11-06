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
          n = x;}
     }
};

class Species{
   public:
      char speciesType;
      std::vector<Instruction> program;
      Species() {}
      Species(std::string name) {
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
   private:
      
      int programCounter;
      int row;
      int column;
      
     
   public:
      Creature(std::string n, Species* species,int r,int c,std::string facing, World* world){
         belongsTo = world;
         type = *species;
         row = r;
         column = c;
         name = n;
         if(strcmp(facing.c_str(),"north") == 0)
            direction = 0;
         else if (strcmp(facing.c_str(),"east") == 0)
            direction = 1;
         else if (strcmp(facing.c_str(),"south") == 0)
            direction = 2;
         else if (strcmp(facing.c_str(),"west") == 0)
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
        _w = std::vector< std::vector<Creature*> >(r, std::vector<Creature*>(c));
        rows = r;
        columns = c;
        for (int i = 0; i < r; i++){
            for (int j = 0; j < c; j++){
               _w[i][j] = NULL;
                
            }  
         }
      }

      void addCreature(Creature* newCreature){
      _w[newCreature->row][newCreature->column] = newCreature;
      }

/*      void addCreature(std::string name, Species* species, int row, int column, std::string direction){
         Creature newCreature = Creature(name, species, row, column, direction, this);
        cout << &newCreature << endl;
	Creature* c = &newCreature;
        cout << c << endl;
         _w[row][column] = c;
      }
*/
      bool isEmpty(int row, int column){
	if(row < 0 || column < 0 || row >= rows || column >= columns)
          return false;
        else if(_w[row][column] != NULL)
          return false;
	return true;
      }
      bool isWall(int row, int column){
	if(row < 0 || column < 0 || row >= rows || column >= columns)
          return true;
        else 
          return false;
      }
      bool isEnemy(int row, int column, Creature* checker){
	if(row < 0 || column < 0 || row >= rows || column >= columns)
          return false;
        else if(_w[row][column] != NULL)
          return false;
	else if(checker->type.speciesType != _w[row][column]->type.speciesType)
          return false;
        else
           return true;
      }
      void infect(int row, int column, Creature* infector){
      _w[row][column]->type = infector->type;
      _w[row][column]->programCounter = 0;
      }

      void printWorld(){
         cout << endl;
         cout << "------------------" << endl;
        // cout << "World at turn: " << turn << endl;
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
      void updateLocation(int row, int col, int newrow, int newcol, Creature* creature){
	_w[newrow][newcol] = creature;
        _w[row][col] = NULL;
      }
      void run(int turns);
};

void Creature::execute(Instruction* instructionToExecute){
   int x = instructionToExecute->n;
   switch ((*instructionToExecute).instructionType){
      case 0:{
         if(direction == 0 && belongsTo->isEmpty(row-1,column)){
            belongsTo->updateLocation(row, column, row - 1, column, this);
            row++;
         }
         if(direction == 1 && belongsTo->isEmpty(row,column+1)){
            belongsTo->updateLocation(row, column, row, column+1, this);
            row++;
         } 
         if(direction == 2 && belongsTo->isEmpty(row+1,column)){
            belongsTo->updateLocation(row, column, row+1, column, this);
            row++;
         } 
         if(direction == 3 && belongsTo->isEmpty(row,column-1)){
            belongsTo->updateLocation(row, column, row, column-1, this);
            row++;
         }    
      }
      case 1:{
         if(direction == 0)
            direction = 3;
         else
            --direction;
      }
      case 2:{
         if(direction == 3)
            direction = 0;
         else
            ++direction;
      }
      case 3:{
         if(direction == 0){
            if(belongsTo->isEnemy(row-1,column,this))
               belongsTo->infect(row-1,column,this);
            else
               ++programCounter;
         }
         if(direction == 1){
            if(belongsTo->isEnemy(row,column+1,this))
               belongsTo->infect(row-1,column,this);
            else
               ++programCounter;
         } 
         if(direction == 2){
            if(belongsTo->isEnemy(row+1,column,this))
               belongsTo->infect(row-1,column,this);
            else
               ++programCounter;
         } 
         if(direction == 3){
            if(belongsTo->isEnemy(row,column-1,this))
               belongsTo->infect(row-1,column,this);
            else
               ++programCounter;     
         }

      }
      case 4:{
         if(direction == 0){
            if(belongsTo->isEmpty(row-1,column))
               programCounter= x;
            else
               ++programCounter;
         }
         if(direction == 1){
            if(belongsTo->isEmpty(row,column+1))
               programCounter= x;
            else
               ++programCounter;
         } 
         if(direction == 2){
            if(belongsTo->isEmpty(row+1,column))
               programCounter= x;
            else
               ++programCounter;
         } 
         if(direction == 3){
            if(belongsTo->isEmpty(row,column-1))
               programCounter= x;
            else
               ++programCounter;     
         }
      }
      case 5:{
         if(direction == 0){
            if(belongsTo->isWall(row-1,column))
               programCounter= x;
            else
               ++programCounter;
         }
         if(direction == 1){
            if(belongsTo->isWall(row,column+1))
               programCounter= x;
            else
               ++programCounter;
         } 
         if(direction == 2){
            if(belongsTo->isWall(row+1,column))
               programCounter= x;
            else
               ++programCounter;
         } 
         if(direction == 3){
            if(belongsTo->isWall(row,column-1))
               programCounter= x;
            else
               ++programCounter;     
         }
      }  
      case 6:{
         srand(0);
         int random = rand();
         if(random%2 == 0)
            ++programCounter;
         else
            programCounter = x;
      }
      case 7:{
         if(direction == 0){
            if(belongsTo->isEnemy(row-1,column,this))
               programCounter= x;
            else
               ++programCounter;
         }
         if(direction == 1){
            if(belongsTo->isEnemy(row,column+1,this))
               programCounter= x;
            else
               ++programCounter;
         } 
         if(direction == 2){
            if(belongsTo->isEnemy(row+1,column,this))
               programCounter= x;
            else
               ++programCounter;
         } 
         if(direction == 3){
            if(belongsTo->isEnemy(row,column-1,this))
               programCounter= x;
            else
               ++programCounter;     
         }
      }
      case 8:{
         programCounter = x;
      }
   }

}
void World::run(int turns){
}

