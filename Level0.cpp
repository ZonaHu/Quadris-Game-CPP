// Level0.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
Level0::Level0(const std::shared_ptr<BoardModel>& p) {
  // constructor
  boardModel_ = p;
}

GenericBlock Level0::generateNextBlock() {
  // using sequence.txt
  GenericLevel::generateNextBlock();
}

void Level0::postMoveOperation() {
  // do nothing in level 0
   }

void Level0::postDropOperation() {
}

