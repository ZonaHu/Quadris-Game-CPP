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
  GenericLevel::generateNextBlock();
}

void Level4::postMoveOperation() {
  boardModel_->down(1);
}

void Level4::postDropOperation() {

}