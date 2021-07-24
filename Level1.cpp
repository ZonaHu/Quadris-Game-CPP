// Level1.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level1::Level1(const std::shared_ptr<BoardModel>& p) {
  // constructor
  boardModel_ = p;
}

GenericBlock Level1::generateNextBlock() {

  GenericLevel::generateNextBlock();

}

void Level1::postMoveOperation() {
  // do nothing in level 1
}

void Level1::postDropOperation() {
  GenericLevel::postDropOperation();
}