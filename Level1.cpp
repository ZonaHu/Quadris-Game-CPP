// Level1.cpp
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

Level1::Level1() {}
Level1::~Level1() {}
void Level1::generateNextBlock() {

  GenericLevel::generateNextBlock();

}
void Level1::postMoveOperation() {
  GenericLevel::postMoveOperation();
}
void Level1::postDropOperation() {
  GenericLevel::postDropOperation();
}