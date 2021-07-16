// Level3.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

Level3::Level3() {}
Level3::~Level3() {}
void Level3::generateNextBlock() { GenericLevel::generateNextBlock(); }
void Level3::postMoveOperation() { GenericLevel::postMoveOperation(); }
void Level3::postDropOperation() { GenericLevel::postDropOperation(); }