// SingleBlock.cpp
// Derived from GenericBlock
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "GenericBlock.h"

// initialize the members with the appropriate values (i.e. type, cells, x, y)
StarBlock::StarBlock() {
  type_ = STAR_BLOCK;
  symbol_ = '*';
  std::vector<std::vector<std::pair<int, int>>> 
                        cells{{{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 
                              {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 
                              {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 
                              {{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
  cells_ = cells;
  rotation_ = 0;
  x_ = 0;
  y_ = 14;
}

StarBlock::~StarBlock() {
  // TODO: implement this

}