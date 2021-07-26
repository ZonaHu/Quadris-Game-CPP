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
  BoardModel_ = std::make_shared<BoardModel> (seed, scriptFile, startLevel, enableBonus); // initialize a board model instance
  isTextOnly_ = isTextOnly; // if set to true, the program is in text-only mode
  controller_ = std::make_unique<Controller> (BoardModel_, enableBonus);
}

//  Starts an infinite game while loop that constantly reads input to the Controller.
//  (game ends on reading EOF)
void GameManager::start() {
  // Initializes the game.
  // Create instance of appropriate Observer derived classes
  // based on value of isTextOnly; subscribe them to the BoardModel.
  if (isTextOnly_){
    std::shared_ptr <Observer> t = std::make_shared<TextDisplay>(BoardModel_);
    BoardModel_->subscribe(t); // subscribe the text display only
  }
  else{
    // subscribe to both displays
    std::shared_ptr<Observer> t = std::make_shared<TextDisplay>(BoardModel_);
    BoardModel_->subscribe(t);
    std::shared_ptr<Observer> g = std::make_shared<GraphicalDisplay>();
    BoardModel_->subscribe(g);
  }
  while(!std::cin.eof()&&!std::cin){
    //Begin an infinite while loop that reads user input from cin into the Controller input overload.
    std::cin >> controller_;


  }
}
