// GraphicalDisplay.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.


#include "GraphicalDisplay.h"

// TODO:
GraphicalDisplay::GraphicalDisplay(std::shared_ptr<BoardModel>) {}
GraphicalDisplay::~GraphicalDisplay() {}

std::shared_ptr<BoardModel> GraphicalDisplay::getBoardModel() const {
  return boardModel_.lock();
}

void GraphicalDisplay::update() {}
