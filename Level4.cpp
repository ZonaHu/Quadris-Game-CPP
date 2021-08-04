// Level4.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "Level4.h"
#include <cstdlib>

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level4::Level4(const std::weak_ptr<BoardModel> p, int seed, bool nonrandom) {
  // constructor
  boardModel_ = p;
  seed_ = seed;
  isNonRandom_ = nonrandom; // determine if in non-random mode or not
  counter_ = 0;
}

void Level4::setCounter(int count) {
  counter_ = count; // used in restart to reset the counter
}

std::shared_ptr <GenericBlock> Level4::generateNextBlock() {
  // generate the next block in level 4
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
  res->setLevelGenerated(4);
  return res;
}

void Level4::postMoveOperation() {
  getBoardModel()->down(1, false, true);
}

void Level4::postDropOperation() {
  // star block generated every time  5 (and also 10, 15, etc.) blocks are placed
  // without clearing at least one row

  int count = getBoardModel()->getNonClearStreak(); // get a counter for non clear streak
  if (count != 0 && count % 5 == 0){
    // start from bottom middle and walk upwards until it finds an empty cell to put a 1x1 block
    // initialize the coordinates
    int x_coord = getBoardModel()->getGridX()/2;
    int y_coord = 0;
    // create a 1*1 star block in the centre column
    std::pair<BlockType, int> TypePair (BlockType::STAR_BLOCK,0);
    // finds an empty cell
    while (getBoardModel()->getCell(x_coord, y_coord).first != BlockType::EMPTY){ // find an empty pair (make sure they're empty blocks)
      y_coord ++;
    }
    getBoardModel()->setCell(x_coord,y_coord,TypePair);
  }
}