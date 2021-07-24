// Level2.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level2::Level2(const std::shared_ptr<BoardModel>& p) {
  // constructor
  boardModel_ = p;
}

GenericBlock Level2::generateNextBlock() {
  // TODO: All blocks are selected with equal probability.
  GenericLevel::generateNextBlock();
}

void Level2::postMoveOperation() {
  // do nothing in level 2
   }

void Level2::postDropOperation() {
  GenericLevel::postDropOperation();
}