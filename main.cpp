// main.cpp
// Derived from GenericBlock
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

# include <iostream>
# include <cstdlib>
# include <string>
# include <sstream>
# include "GameManager.h"
# include <memory>

int main(int argc, char *argv[]){
  // initialize the variables to default values
  bool isTextOnly = false; // the default behaviour is to show both text and graphics
  int seed = 1; // the default seed
  std::string scriptFile = "sequence.txt"; // default sequence source file for level 0
  int startLevel = 0; // default starting level is level 0
  bool enableBonus = false;  // default bonus features status
  // we need to handle some options for command line interface
  // read in the arguments
  for (int i = 1; i < argc; i++){
    // command line arg is "-text"
    if (strcmp(argv[i],"-text") == 0){ // check if the contents of the two strings are the same.
      isTextOnly = true;
    }
      // command line arg is "-seed xxx"
    else if (strcmp(argv[i],"-seed") == 0){
      // we want to convert the seed to a number from command line argument
      seed = std::stoi(argv[i+1]);
    }
      // command line arg is "-scriptfile xxx"
    else if (strcmp(argv[i],"-scriptfile") == 0){
      scriptFile = argv[i+1];
    }
      // command line arg is "-startlevel n"
    else if (strcmp(argv[i],"-startlevel") == 0){
      // we want to convert n to a number from command line argument
      startLevel = std::stoi(argv[i+1]);
    }
      // bonus features
    else if (strcmp(argv[i],"-enablebonus") == 0){
      enableBonus = true;
    }
    // TODO: other command line args?
  }
  // Creates an instance of GameManager, passing in the CLI args.
  std::unique_ptr <GameManager> theManager = std::make_unique<GameManager> (isTextOnly,seed,scriptFile,
                                                                            startLevel, enableBonus);
  theManager->start();
  return 0;
}
