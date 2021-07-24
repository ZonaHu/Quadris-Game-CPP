// Level3.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level3::Level3(const std::shared_ptr<BoardModel>& p) {
  // constructor
  boardModel_ = p;
}

GenericBlock Level3::generateNextBlock() {
  // generate the next block in level 3
  GenericBlock res;
  BlockType curType;
  int num = rand() % 9;
  // S and Z are selected with a probability of 2/9 each
  if (num == 0 || num == 1){
    curType = S_BLOCK;
  }
  else if (num == 2 || num == 3){
    curType = Z_BLOCK;
  }
    // other blocks are selected with a probability of 1/9 each (and no star block in this level)
  else if (num == 4){
    curType = T_BLOCK;
  }
  else if (num == 5){
    curType = O_BLOCK;
  }
  else if (num == 6){
    curType = L_BLOCK;
  }
  else if (num == 7){
    curType = J_BLOCK;
  }
  else if (num == 8){
    curType = I_BLOCK;
  }
  res.setType(curType); // set the current type in the generic block
  return res;
}

void Level3::postMoveOperation() {
  // blocks generated in level 3 are "heavy"
  boardModel_->down(1); //downward move of one row if possible
}

void Level3::postDropOperation() {
  // do nothing in level 3
}