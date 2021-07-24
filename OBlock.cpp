// OBlock.cpp
// Derived from GenericBlock
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "GenericBlock.h"

// initialize the members with the appropriate values (i.e. type, cells, x, y)
OBlock::OBlock() {
  type_ = O_BLOCK;
  symbol_ = 'O';
  std::vector<std::vector<std::pair<int, int>>> 
                        cells{{{0, 0}, {0, 1}, {1, 0}, {1, 1}}, 
                              {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, 
                              {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, 
                              {{0, 0}, {0, 1}, {1, 0}, {1, 1}}};
  cells_ = cells;
  rotation_ = 0;
  x_ = 0;
  y_ = 13;
}

OBlock::~OBlock() {
  // TODO: implement this

}
