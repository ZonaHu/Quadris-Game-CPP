//
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_CONTROLLER_H
#define PROJECT_2_3_CONTROLLER_H
#include "BoardModel.h"
#include <string>
#include <cstdlib>

class Controller {
private:
  BoardModel* boardModel_; // Pointer to BoardModel.
  std::vector <std::string> commandList_;  // vector of strings representing each command name

// TODO; update

public:
  Controller();
  ~Controller();
  friend std::istream &operator>>(std::istream &, Controller &); //  Pass cin input to extractMultiplier().
  bool parse(std::string, std::string);
};

#endif // PROJECT_2_3_CONTROLLER_H
