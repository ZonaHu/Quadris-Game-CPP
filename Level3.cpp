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


}

void Level3::postMoveOperation() {
  // blocks generated in level 3 are "heavy"
  boardModel_->down(1); //downward move of one row if possible
}

void Level3::postDropOperation() {
  // do nothing in level 3
}