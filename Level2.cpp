// Level2.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "Level2.h"
#include <cstdlib>

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level2::Level2(const std::weak_ptr<BoardModel> p, int seed) {
  // constructor
  boardModel_ = p;
  seed_ = seed;
}

std::shared_ptr <GenericBlock> Level2::generateNextBlock() {
  // generate the next block in level 2
  std::shared_ptr<GenericBlock> res;
  static std::mt19937 rng(seed_);
  int num = abs((int) rng()) % 7;
  // All blocks are selected with equal probability.
  // and no star block in this level
  if (num == 0){
    res = std::make_shared<SBlock>();
  }
  else if (num == 1){
    res = std::make_shared<ZBlock>();
  }
  else if (num == 2){
    res = std::make_shared<TBlock>();
  }
  else if (num == 3){
    res = std::make_shared<OBlock>();
  }
  else if (num == 4){
    res = std::make_shared<LBlock>();
  }
  else if (num == 5){
    res = std::make_shared<JBlock>();
  }
  else if (num == 6){
    res = std::make_shared<IBlock>();
  }
  res->setLevelGenerated(2);
  return res;
}

void Level2::postMoveOperation() {
  // do nothing in level 2
}

void Level2::postDropOperation() {
  // do nothing in level 2
}
void Level2::setCounter(int) {
  // do nothing in level 2
}
