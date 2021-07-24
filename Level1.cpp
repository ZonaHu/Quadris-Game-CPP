// Level1.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level1::Level1(const std::shared_ptr<BoardModel>& p) {
  // constructor
  boardModel_ = p;
}

GenericBlock Level1::generateNextBlock() {
  // generate the next block in level 1
  GenericBlock res;
  BlockType curType;
  int num = rand() % 12;
  // S and Z are selected with a probability of 1/12 each
  if (num == 0){
    curType = S_BLOCK;
  }
  else if (num == 1){
    curType = Z_BLOCK;
  }
  // other blocks are selected with a probability of 1/6 each (and no star block in this level)
  else if (num == 2 || num == 3){
    curType = T_BLOCK;
  }
  else if (num == 4 || num == 5){
    curType = O_BLOCK;
  }
  else if (num == 6 || num == 7){
    curType = L_BLOCK;
  }
  else if (num == 8 || num == 9){
    curType = J_BLOCK;
  }
  else if (num == 10 || num == 11){
    curType = I_BLOCK;
  }
  res.setType(curType); // set the current type in the generic block
  return res;
}

void Level1::postMoveOperation() {
  // do nothing in level 1
}

void Level1::postDropOperation() {
  // do nothing in level 1
}