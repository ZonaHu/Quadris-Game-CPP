// GraphicalDisplay.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.


#include "GraphicalDisplay.h"

// The graphical display should be set up in a similar way to the text diaplay,
// showing the current board, the current block, the next block to come, and the scoreboard in a single window
GraphicalDisplay::GraphicalDisplay(std::shared_ptr<BoardModel>) {}
GraphicalDisplay::~GraphicalDisplay() {}

std::shared_ptr<BoardModel> GraphicalDisplay::getBoardModel() const {
  return boardModel_.lock();
}

void GraphicalDisplay::update() {}
