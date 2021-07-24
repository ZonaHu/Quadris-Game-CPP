// Level0.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level0::Level0(const std::shared_ptr<BoardModel>& p, std::vector<char> blockType) {
  // constructor
  boardModel_ = p;
  blockSeq_ = blockType;
  counter_ = 0;
}

GenericBlock Level0::generateNextBlock() {
  GenericBlock res;
  char typeBlock = blockSeq_.at(counter_);
  BlockType curType;
  if (typeBlock == 'I'){
    curType = I_BLOCK;
  }
  else if (typeBlock == 'J'){
    curType = J_BLOCK;
  }
  else if (typeBlock == 'L'){
    curType = L_BLOCK;
  }
  else if (typeBlock == 'O'){
    curType = O_BLOCK;
  }
  else if (typeBlock == 'S'){
    curType = S_BLOCK;
  }
  else if (typeBlock == 'Z'){
    curType = Z_BLOCK;
  }
  else if (typeBlock == 'T'){
    curType = T_BLOCK;
  }
  counter_++;
  res.setType(curType); // set the current type in the generic block
  return res;
}

void Level0::postMoveOperation() {
  // do nothing in level 0
}

void Level0::postDropOperation() {
  // do nothing in level 0
}

