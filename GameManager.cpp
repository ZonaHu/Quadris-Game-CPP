// GameManager.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "GameManager.h"
#include "Controller.h"
#include "BoardModel.h"
#include "GenericLevel.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include <memory>

/* Create instance of BoardModel passing the following to the constructor (seed, scriptFile, startLevel).
Create instance of  appropriate Observer derived classes based on value of isTextOnly; subscribe them to the BoardModel.
Create an instance of Controller passing BoardModel to the constructor.
Begin an infinite while loop that reads user input from cin into the Controller input overload.*/

GameManager::GameManager(bool isTextOnly, int seed, std::string scriptFile,
                         int startLevel, bool enableBonus) {
  // int seed  sets the random number generator's seed to this number
  // std::string scriptFile source of blocks for level 0
  // int startLevel starts the game in this level
  // bool enableBonus activates bonus features if true

  // Instantiate Controller
  controller_ = std::make_shared<Controller> (enableBonus);

  // Read in the block sequence for Level0
  std::vector<BlockType> level0BlockSeq = controller_->blockSequenceSource(scriptFile);
  if (level0BlockSeq.size() == 0) {
    std::cout << "Using sequence.txt for Level0 instead." << std::endl;
    level0BlockSeq = controller_->blockSequenceSource("sequence.txt");
  }

  // Instantiate BoardModel
  BoardModel_ = std::make_shared<BoardModel> (seed, scriptFile, startLevel, enableBonus); // initialize a board model instance

  // Instantiate all the levels and store them in an array
  std::vector <std::shared_ptr<GenericLevel>> levelArray;
  std::shared_ptr<GenericLevel> level0 = std::make_shared<Level0>(BoardModel_, level0BlockSeq);
  std::shared_ptr<GenericLevel> level1 = std::make_shared<Level1>(BoardModel_, seed);
  std::shared_ptr<GenericLevel> level2 = std::make_shared<Level2>(BoardModel_, seed);
  std::shared_ptr<GenericLevel> level3 = std::make_shared<Level3>(BoardModel_, seed, false);
  std::shared_ptr<GenericLevel> level4 = std::make_shared<Level4>(BoardModel_, seed, false);
  levelArray.push_back(level0);
  levelArray.push_back(level1);
  levelArray.push_back(level2);
  levelArray.push_back(level3);
  levelArray.push_back(level4);

  BoardModel_->setLevels(levelArray);
  controller_->setBoard(BoardModel_);

  isTextOnly_ = isTextOnly; // if set to true, the program is in text-only mode
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
    std::shared_ptr <Observer> t = std::make_shared<TextDisplay>(BoardModel_);
    BoardModel_->subscribe(t);
    std::shared_ptr <Observer> g = std::make_shared<GraphicalDisplay>(BoardModel_);
    BoardModel_->subscribe(g);
  }
  while(!std::cin.eof()||!std::cin.fail()){
    //Begin an infinite while loop that reads user input from cin into the Controller input overload.
    std::cin >> *controller_; // * allowed here since not expressing ownership.
  }
}
