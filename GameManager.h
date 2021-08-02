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
#include "TextDisplay.h"
#include "GraphicalDisplay.h"
#include <memory>

class GameManager {
private:
  // support the options as command line args
  bool isTextOnly_; // if set to true, the program is in text-only mode
  std::shared_ptr<BoardModel> BoardModel_; // BoardModel on stack.
  std::shared_ptr<Controller> controller_; // Controller on stack

public:
  GameManager(bool isTextOnly, int seed, std::string scriptFile, int startLevel, bool enableBonus); //  constructor
  ~GameManager()= default; // destructor
  void start(); // Initializes the game, game ends on reading EOF
};

#endif // PROJECT_2_3_GAMEMANAGER_H
