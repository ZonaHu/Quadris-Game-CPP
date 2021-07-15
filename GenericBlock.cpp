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

void GenericBlock::setType() {}

std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>,
                       std::pair<int, int>, std::pair<int, int>>>
GenericBlock::getCells() {
  return std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>,
                                std::pair<int, int>, std::pair<int, int>>>();
}

void GenericBlock::setCells() {}
int GenericBlock::getRotation() const { return 0; }
void GenericBlock::setRotation() {}
std::pair<int, int> GenericBlock::getCoords() const {
  return std::pair<int, int>();
}
void GenericBlock::setCoords() {}
