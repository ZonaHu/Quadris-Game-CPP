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
  std::vector <std::string> commandList_;  // vector of strings representing each command name
  std::map <std::string, std::vector<std::tuple<int, int, std::string>>> macroMap_;
  std::vector <std::tuple<int, int, std::string>> tempMacroStore_;
  std::string tempMacroName_;
  bool macroInputFlag_;
  bool enableBonus_;
  bool parse(std::string, std::string);
  void rename(std::vector <std::string>);
  void macro(std::vector <std::string>);
  void execCommand(std::string, int);
  std::vector <BlockType> norandom(std::string);
  void sequence(std::string);
  
public:
  Controller(std::shared_ptr <BoardModel>, bool);
  ~Controller();
  void extractMultiplier(std::string);
  std::vector <BlockType> blockSequenceSource(std::string);
  friend std::istream &operator>>(std::istream &, Controller &control); //  Pass cin input to extractMultiplier().

};

#endif // PROJECT_2_3_CONTROLLER_H
