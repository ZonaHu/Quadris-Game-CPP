// Level0.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level0::Level0(const std::shared_ptr<BoardModel> p, std::vector<BlockType> blockSeq) {
  // constructor
  boardModel_ = p;
  blockSeq_ = blockType;
  counter_ = 0;
}

std::shared_ptr <GenericBlock> Level0::generateNextBlock() {  // level 0 follows the sequence file
  std::shared_ptr<GenericBlock> res;
  // read the block type from the vector at the correct index
  char typeBlock = blockSeq_.at(counter_);
  BlockType curType;
  // identify the type
  if (typeBlock == 'I'){
    curType = I_BLOCK;
    res = std::make_shared<IBlock>();
  }
  else if (typeBlock == 'J'){
    curType = J_BLOCK;
    res = std::make_shared<JBlock>();
  }
  else if (typeBlock == 'L'){
    curType = L_BLOCK;
    res = std::make_shared<LBlock>();
  }
  else if (typeBlock == 'O'){
    curType = O_BLOCK;
    res = std::make_shared<OBlock>();
  }
  else if (typeBlock == 'S'){
    curType = S_BLOCK;
    res = std::make_shared<SBlock>();
  }
  else if (typeBlock == 'Z'){
    curType = Z_BLOCK;
    res = std::make_shared<ZBlock>();
  }
  else if (typeBlock == 'T'){
    curType = T_BLOCK;
    res = std::make_shared<TBlock>();
  }
  counter_++; // increment the counter
  res->setType(curType); // set the current type in the generic block
  return res;
}

void Level0::postMoveOperation() {
  // do nothing in level 0
}

void Level0::postDropOperation() {
  // do nothing in level 0
}

