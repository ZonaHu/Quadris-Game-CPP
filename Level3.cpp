// Level3.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "Level3.h"
#include <stdlib.h> 

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level3::Level3(const std::shared_ptr<BoardModel> p, int seed, bool nonrandom) {
  // constructor
  boardModel_ = p;
  seed_ = seed;
  isNonRandom_ = nonrandom; // determine if in non-random mode or not
  counter_ = 0;
}

std::shared_ptr <GenericBlock> Level3::generateNextBlock() {
  // generate the next block in level 3
  std::shared_ptr<GenericBlock> res;
  if (isNonRandom_){ // if in non-random mode
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
  }
  else{ // if in random mode
    static std::mt19937 rng(seed_);
    int num = abs((int) rng()) % 9;
    // S and Z are selected with a probability of 2/9 each
    if (num == 0 || num == 1){
      res = std::make_shared<SBlock>();
    }
    else if (num == 2 || num == 3){
      res = std::make_shared<ZBlock>();
    }
      // other blocks are selected with a probability of 1/9 each (and no star block in this level)
    else if (num == 4){
      res = std::make_shared<TBlock>();
    }
    else if (num == 5){
      res = std::make_shared<OBlock>();
    }
    else if (num == 6){
      res = std::make_shared<LBlock>();
    }
    else if (num == 7){
      res = std::make_shared<JBlock>();
    }
    else if (num == 8){
      res = std::make_shared<IBlock>();
    }
  }
  return res;
}

void Level3::postMoveOperation() {
  // blocks generated in level 3 are "heavy"
  boardModel_->down(1, false); //downward move of one row if possible
}

void Level3::postDropOperation() {
  // do nothing in level 3
}