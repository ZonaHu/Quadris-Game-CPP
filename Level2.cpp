// Level2.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level2::Level2(const std::shared_ptr<BoardModel>& p) {
  // constructor
  boardModel_ = p;
}

GenericBlock Level2::generateNextBlock() {
  // generate the next block in level 2
  GenericBlock res;
  BlockType curType;
  int num = rand() % 7;
  // All blocks are selected with equal probability.
  // and no star block in this level
  if (num == 0){
    curType = S_BLOCK;
  }
  else if (num == 1){
    curType = Z_BLOCK;
  }
  else if (num == 2){
    curType = T_BLOCK;
  }
  else if (num == 3){
    curType = O_BLOCK;
  }
  else if (num == 4){
    curType = L_BLOCK;
  }
  else if (num == 5){
    curType = J_BLOCK;
  }
  else if (num == 6){
    curType = I_BLOCK;
  }
  res.setType(curType); // set the current type in the generic block
  return res;
}

void Level2::postMoveOperation() {
  // do nothing in level 2
}

void Level2::postDropOperation() {
  // do nothing in level 2
}