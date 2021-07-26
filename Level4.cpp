// Level4.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level4::Level4(const std::shared_ptr<BoardModel>& p, int seed) {
  // constructor
  boardModel_ = p;
  seed_ = seed;
}

std::shared_ptr <GenericBlock> Level4::generateNextBlock() {
  // generate the next block in level 4
  std::shared_ptr<GenericBlock> res;
  BlockType curType;
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
    // other blocks are selected with a probability of 1/9 each
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
  res->setType(curType); // set the current type in the generic block
  return res;
}

void Level4::postMoveOperation() {
  boardModel_->down(1);
}

void Level4::postDropOperation() {
  // star block generated every time  5 (and also 10, 15, etc.) blocks are placed
  // without clearing at least one row

  int count = boardModel_->getNonClearStreak(); // get a counter for non clear streak
  if (count % 5 == 0){
    // get a copy of the current grid
    std::vector<std::vector<std::pair<BlockType, int>>> curGrid = boardModel_->getGrid();
    // start from bottom middle and walk upwards until it finds an empty cell to put a 1x1 block
    // initialize the coordinates
    int x_coord = curGrid.size()/2;
    int y_coord = curGrid.at(0).size()/2;
    // create a 1*1 star block in the centre column
    std::pair<BlockType, int> TypePair (STAR_BLOCK,0);
    // finds an empty cell
    while (curGrid.at(x_coord).at(y_coord).second != 0 ||
        curGrid.at(x_coord).at(y_coord).first == EMPTY ){ // find an empty pair (make sure they're empty blocks)
      y_coord ++;
    }
    boardModel_.setCell(x_coord,y_coord,TypePair); // reset the grids
  }
}