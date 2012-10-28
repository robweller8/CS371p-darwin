



class  World{
   private int r;
   private int c;
   World(r,c){
      std::vector< std::vector<Creature> >(r, std::vector<Creature>(c, NULL));
   }
   // define index operator

  
   
}
class Creature{
   int direction;
   int programCounter;
   private std::vector<Instruction>;
}


class Instruction{
   private std::string instructionType;
   private int n;
   Instruction (std::string name){
     instructionType = name;
     n = 0;
   }
   Intruction (std::string name, int x){
      instructionType = name;
      n = x;
   }
   void execute(){
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

}

class god{
}
