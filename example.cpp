#include <iostream>

#include <random>

#include "example.h"

namespace example {
   std::string print_hello_world() {
     return "Hello World!";
   }

   int roll_dice() {
      std::default_random_engine generator;
      std::uniform_int_distribution<int> distribution(1,6);
     return distribution(generator); 
   }
   
}
