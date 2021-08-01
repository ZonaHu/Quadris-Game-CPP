// Level0.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "Level0.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level0::Level0(const std::weak_ptr<BoardModel> p, std::vector<BlockType> blockSeq) {
  // constructor
  boardModel_ = p;
  blockSeq_ = blockSeq;
  counter_ = 0;
}

std::shared_ptr <GenericBlock> Level0::generateNextBlock() {  // level 0 follows the sequence file
  std::shared_ptr<GenericBlock> res;
  // read the block type from the vector at the correct index
  BlockType typeBlock = blockSeq_.at(counter_);
  // identify the type
  if (typeBlock == BlockType::I_BLOCK){
    res = std::make_shared<IBlock>();
  }
  else if (typeBlock == BlockType::J_BLOCK){
    res = std::make_shared<JBlock>();
  }
  else if (typeBlock == BlockType::L_BLOCK){
    res = std::make_shared<LBlock>();
  }
  else if (typeBlock == BlockType::O_BLOCK){
    res = std::make_shared<OBlock>();
  }
  else if (typeBlock == BlockType::S_BLOCK){
    res = std::make_shared<SBlock>();
  }
  else if (typeBlock == BlockType::Z_BLOCK){
    res = std::make_shared<ZBlock>();
  }
  else if (typeBlock == BlockType::T_BLOCK){
    res = std::make_shared<TBlock>();
  }
  if (counter_ == (int)blockSeq_.size() - 1) {
    counter_ = 0;
  } else {
    counter_++; // increment the counter
  }
  return res;
}

void Level0::postMoveOperation() {
  // do nothing in level 0
}

void Level0::postDropOperation() {
  // do nothing in level 0
}

