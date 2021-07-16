// GameManager.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_GAMEMANAGER_H
#define PROJECT_2_3_GAMEMANAGER_H
#include <string>
#include <iostream>
#include "BoardModel.h"
#include "Controller.h"

class GameManager {
private:
  // support the options as command line args
  bool isTextOnly_; // if set to true, the program is in text-only mode
  int seed_; // sets the random number generator's seed to this number
  std::string scriptFile_; // source of blocks for level 0
  int startLevel_; // starts the game in this level
  BoardModel* BoardModel_; // Pointer to BoardModel.
  Controller* controller_; // pointer to Controller object

public:
  GameManager(); // default constructor
  ~GameManager(); // destructor
  void start(); // Initializes the game, game ends on reading EOF
};

#endif // PROJECT_2_3_GAMEMANAGER_H
