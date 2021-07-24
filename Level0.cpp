// Level0.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

Level0::Level0(const std::shared_ptr<BoardModel> &unnamed)
    : GenericLevel(unnamed) {
}
Level0::~Level0() {}

GenericBlock Level0::generateNextBlock() {
  GenericLevel::generateNextBlock();
}

void Level0::postMoveOperation() { GenericLevel::postMoveOperation(); }
void Level0::postDropOperation() { GenericLevel::postDropOperation(); }

