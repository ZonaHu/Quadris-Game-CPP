// Level2.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

Level2::Level2() {}
Level2::~Level2() {}
void Level2::generateNextBlock() { GenericLevel::generateNextBlock(); }
void Level2::postMoveOperation() { GenericLevel::postMoveOperation(); }
void Level2::postDropOperation() { GenericLevel::postDropOperation(); }