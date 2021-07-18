// GenericBlock.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "GenericBlock.h"

GenericBlock::GenericBlock() {
  // TODO: implement this
}

GenericBlock::~GenericBlock() {
  // TODO: implement this
}

// TODO: implement the rest
BlockType GenericBlock::getType() const { return L; }
void GenericBlock::setType(BlockType type) { type_ = type; }

std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>,
                       std::pair<int, int>, std::pair<int, int>>>
GenericBlock::getCells() { return cells_; }

int GenericBlock::getRotation() const { return rotation_; }
void GenericBlock::setRotation(int rotation) { rotation_ = rotation; }

std::pair<int, int> GenericBlock::getCoords() const {return std::pair<int, int>{x_, y_}; }
void GenericBlock::setCoords(int x, int y) {
  x_ = x;
  y_ = y;
}
