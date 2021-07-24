// JBlock.cpp
// Derived from GenericBlock
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "GenericBlock.h"

// initialize the members with the appropriate values (i.e. type, cells, x, y)
JBlock::JBlock() {
  type_ = J_BLOCK;
  symbol_ = 'J';
  std::vector<std::vector<std::pair<int, int>>>
                        cells{{{0, 0}, {0, 1}, {1, 0}, {2, 0}}, 
                              {{0, 0}, {0, 1}, {0, 2}, {1, 2}}, 
                              {{0, 1}, {1, 1}, {2, 0}, {2, 1}}, 
                              {{0, 0}, {1, 0}, {1, 2}, {1, 3}}};
  cells_ = cells;
  rotation_ = 0;
  x_ = 0;
  y_ = 13;
}

JBlock::~JBlock() {
  // TODO: implement this

}
