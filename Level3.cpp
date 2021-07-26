// Level3.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level3::Level3(const std::shared_ptr<BoardModel> p, int seed, bool nonrandom, std::vector<char> blockType) {
  // constructor
  boardModel_ = p;
  seed_ = seed;
  nonRandom_ = nonrandom; // determine if in non-random mode or not
  blockSeq_ = blockType; // sequence of blocks given in a file in non random mode
  counter_ = 0;
}

std::shared_ptr <GenericBlock> Level3::generateNextBlock() {
  // generate the next block in level 3
  std::shared_ptr<GenericBlock> res;
  BlockType curType;
  if (nonRandom_){ // if in non-random mode
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
  }
  else{ // if in random mode
    static std::mt19937 rng(seed_);
    int num = (int) rng() % 9;
    // S and Z are selected with a probability of 2/9 each
    if (num == 0 || num == 1){
      curType = S_BLOCK;
      res = std::make_shared<SBlock>();
    }
    else if (num == 2 || num == 3){
      curType = Z_BLOCK;
      res = std::make_shared<ZBlock>();
    }
      // other blocks are selected with a probability of 1/9 each (and no star block in this level)
    else if (num == 4){
      curType = T_BLOCK;
      res = std::make_shared<TBlock>();
    }
    else if (num == 5){
      curType = O_BLOCK;
      res = std::make_shared<OBlock>();
    }
    else if (num == 6){
      curType = L_BLOCK;
      res = std::make_shared<LBlock>();
    }
    else if (num == 7){
      curType = J_BLOCK;
      res = std::make_shared<JBlock>();
    }
    else if (num == 8){
      curType = I_BLOCK;
      res = std::make_shared<IBlock>();
    }
  }
  res->setType(curType); // set the current type in the generic block
  return res;
}

void Level3::postMoveOperation() {
  // blocks generated in level 3 are "heavy"
  boardModel_->down(1); //downward move of one row if possible
}

void Level3::postDropOperation() {
  // do nothing in level 3
}