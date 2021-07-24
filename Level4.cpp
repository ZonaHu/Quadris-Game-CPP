// Level4.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level4::Level4(const std::shared_ptr<BoardModel>& p) {
  // constructor
  boardModel_ = p;
}

GenericBlock Level4::generateNextBlock() {
  // generate the next block in level 4
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
    // other blocks are selected with a probability of 1/9 each
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

void Level4::postMoveOperation() {
  boardModel_->down(1);
}

void Level4::postDropOperation() {
  // star block generated every time  5 (and also 10, 15, etc.) blocks are placed
  // without clearing at least one row

  int count = boardModel_->getNonClearStreak(); // get a counter for non clear streak
  if (count%5 == 0){
    // create a 1*1 star block in the centre column
    // start from bottom middle and walk upwards until it finds an empty cell to put a 1x1 block
    std::vector <std::vector <char>> curGrid = boardModel_->getGrid();
    // TODO: finish the rest


  }
}