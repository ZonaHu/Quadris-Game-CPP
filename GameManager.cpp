// GameManager.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "GameManager.h"
#include <memory>

/* Create instance of BoardModel passing the following to the constructor (seed, scriptFile, startLevel).
Create instance of  appropriate Observer derived classes based on value of isTextOnly; subscribe them to the BoardModel.
Create an instance of Controller passing BoardModel to the constructor.
Begin an infinite while loop that reads user input from cin into the Controller input overload.*/

GameManager::GameManager(bool isTextOnly, int seed, std::string scriptFile,
                         int startLevel, bool enableBonus) {
  // initialize all private members
  BoardModel_ = std::make_shared<BoardModel>(); // initialize a board model instance
  isTextOnly_ = isTextOnly; // if set to true, the program is in text-only mode
  seed_ = seed; // sets the random number generator's seed to this number
  std::string scriptFile_ = scriptFile; // source of blocks for level 0
  int startLevel_ = startLevel; // starts the game in this level
  enableBonus_ = enableBonus;
  controller_ = std::make_unique<Controller>(BoardModel_);
}

//  Starts an infinite game while loop that constantly reads input to the Controller.
//  (game ends on reading EOF)
void GameManager::start() {
  // Initializes the game.
  // Create instance of appropriate Observer derived classes
  // based on value of isTextOnly; subscribe them to the BoardModel.
  if (isTextOnly_){
    std::unique_ptr <TextDisplay> t = std::make_unique<TextDisplay>();
    BoardModel_->subscribe(t); // TODO: Is this correct? currently, it says "No viable conversion from 'std::unique_ptr<TextDisplay>' to 'Observer *"
  }
  else{
    std::unique_ptr <TextDisplay> t = std::make_unique<TextDisplay>();
    BoardModel_->subscribe(t);
    std::unique_ptr <GraphicalDisplay> g = std::make_unique<GraphicalDisplay>();
    BoardModel_->subscribe(g);
  }
  while(!std::cin.eof()&&!std::cin){
    //Begin an infinite while loop that reads user input from cin into the Controller input overload.
    std::cin >> controller_;
    // TODO: how to pass the private members?
  }
}
