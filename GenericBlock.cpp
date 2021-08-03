// GenericBlock.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "GenericBlock.h"

BlockType GenericBlock::getType() const { return type_; } // getter for the type of a block
void GenericBlock::setType(BlockType type) { type_ = type; } // setter for the type of a block

std::vector<std::vector<std::pair<int, int>>>
GenericBlock::getCells() { return cells_; } // getter for the cells

int GenericBlock::getRotation() const { return rotation_; } // getter for rotation
void GenericBlock::setRotation(int rotation) { rotation_ = rotation; } // setter for the rotation

// getter for the coordinates
std::pair<int, int> GenericBlock::getCoords() const {return std::pair<int, int>{x_, y_}; }

// setter for the coordinates
void GenericBlock::setCoords(int x, int y) {
  x_ = x;
  y_ = y;
}