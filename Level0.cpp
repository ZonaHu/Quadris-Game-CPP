// Level0.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

Level0::Level0() {}
Level0::~Level0() {}
void Level0::generateNextBlock() { GenericLevel::generateNextBlock(); }
void Level0::postMoveOperation() { GenericLevel::postMoveOperation(); }
void Level0::postDropOperation() { GenericLevel::postDropOperation(); }