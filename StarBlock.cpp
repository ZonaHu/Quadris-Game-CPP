// SingleBlock.cpp
// Derived from GenericBlock
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "GenericBlock.h"

// initialize the members with the appropriate values (i.e. type, cells, x, y)
StarBlock::StarBlock() {
  type_ = BlockType::STAR_BLOCK;
  // coordinates for cells based on the rotation
  // each containing the relative coordinates (relative to bottom left) of the cells in pairs.
  // Each index represents a rotation (i.e. cells[0] is 0 deg, cells[1] is 90 deg, etc).
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
