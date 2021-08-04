// Controller.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_CONTROLLER_H
#define PROJECT_2_3_CONTROLLER_H
#include "BoardModel.h"
#include "GenericBlock.h"
#include <string>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <iostream>
#include <memory>

class Controller {
private:
  std::shared_ptr <BoardModel> boardModel_; // Pointer to BoardModel.
  std::vector <std::string> commandList_;  // Vector of strings representing each command name.
  std::map <std::string, std::vector<std::tuple<int, int, std::string>>> macroMap_; // For storing maccros and their related commands.
  std::vector <std::tuple<int, int, std::string>> tempMacroStore_; //
  std::string tempMacroName_; // When a user is entering a macro, the name first gets stored here.
  bool macroInputFlag_; // For storing whether the user is inputting commands that need to be executed immediately, or they are entering a macro.
  bool enableBonus_; // Flag for enabling bonus features like macro and renaming.
  bool parse(std::string, std::string); // For comparing command input against current valid command names.
  void rename(std::vector <std::string>);  // For updating command names.
  void macro(std::vector <std::string>); // Handles macro arguments such as new, save, and exec.
  void execCommand(std::string, int); // After recognizing a valid command, executes it's relevant function.
  void sequence(std::string); // For reading in from a file that contains commands to execute.
  
public:
  Controller(bool); // Constructor, takes in a boolean flag for enabling controller related bonus features.
  ~Controller(); // Destructor.
  void extractMultiplier(std::string); // For getting the number of times a specific command needs to run.
  std::vector <BlockType> blockSequenceSource(std::string); // For reading in from a file to get the blocks we need for some commands.
  void setBoard(std::shared_ptr <BoardModel>); // For setting boardModel_.
  friend std::istream &operator>>(std::istream &, Controller &control); //  Pass cin input to extractMultiplier().

};

#endif // PROJECT_2_3_CONTROLLER_H
