// Controller.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_CONTROLLER_H
#define PROJECT_2_3_CONTROLLER_H
#include "BoardModel.h"
#include <string>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <iostream>

class Controller {
private:
  std::shared_ptr <BoardModel> boardModel_; // Pointer to BoardModel.
  std::vector <std::string> commandList_;  // vector of strings representing each command name
  std::map <std::string, std::vector<std::tuple<int, int, std::string>>> macroMap_;
  std::vector<std::tuple<int, int, std::string>> tempMacroStore_;
  std::string tempMacroName_;
  bool macroInputFlag_;
  bool parse(std::string, std::string);
  void rename(std::vector <std::string> args);
  void macro(std::vector <std::string> args);
  void extractMultiplier(std::string);
  void execCommand(std::string, int);

public:
  Controller(std::shared_ptr <BoardModel>);
  ~Controller();
  friend std::istream &operator>>(std::istream &, Controller &); //  Pass cin input to extractMultiplier().
};

#endif // PROJECT_2_3_CONTROLLER_H
