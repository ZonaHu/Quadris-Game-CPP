// Level4.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

Level4::Level4() {}
Level4::~Level4() {}

GenericBlock Level4::generateNextBlock() {
  GenericLevel::generateNextBlock();
}

void Level4::postMoveOperation() { GenericLevel::postMoveOperation(); }
void Level4::postDropOperation() { GenericLevel::postDropOperation(); }