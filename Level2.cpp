// Level2.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level2::Level2(const std::shared_ptr<BoardModel>& p, int seed) {
  // constructor
  boardModel_ = p;
  seed_ = seed;
}

std::shared_ptr <GenericBlock> Level2::generateNextBlock() {
  // generate the next block in level 2
  std::shared_ptr<GenericBlock> res;
  BlockType curType;
  static std::mt19937 rng(seed_);
  int num = (int) rng() % 7;
  // All blocks are selected with equal probability.
  // and no star block in this level
  if (num == 0){
    curType = S_BLOCK;
    res = std::make_shared<SBlock>();
  }
  else if (num == 1){
    curType = Z_BLOCK;
    res = std::make_shared<ZBlock>();
  }
  else if (num == 2){
    curType = T_BLOCK;
    res = std::make_shared<TBlock>();
  }
  else if (num == 3){
    curType = O_BLOCK;
    res = std::make_shared<OBlock>();
  }
  else if (num == 4){
    curType = L_BLOCK;
    res = std::make_shared<LBlock>();
  }
  else if (num == 5){
    curType = J_BLOCK;
    res = std::make_shared<JBlock>();
  }
  else if (num == 6){
    curType = I_BLOCK;
    res = std::make_shared<IBlock>();
  }
  res->setType(curType); // set the current type in the generic block
  return res;
}

void Level2::postMoveOperation() {
  // do nothing in level 2
}

void Level2::postDropOperation() {
  // do nothing in level 2
}