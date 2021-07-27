//
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.


#include "TextDisplay.h"

TextDisplay::TextDisplay(std::shared_ptr<BoardModel> boardModel) {
  boardModel_ = boardModel;
}

void TextDisplay::update() {
  std::cout << "TEXT DISPLAY" << std::endl;
  std::cout << boardModel_->getScore() << std::endl;

  std::vector <std::vector <std::pair<BlockType, int>>> grid = boardModel_->getGrid();
  std::shared_ptr<GenericBlock> curBlock = boardModel_->getCurBlock();
  int r = curBlock->getRotation();
  std::pair <int, int> base = curBlock->getCoords();
  std::pair <int, int> a = curBlock->getCells().at(r).at(0);
  std::pair <int, int> b = curBlock->getCells().at(r).at(1);
  std::pair <int, int> c = curBlock->getCells().at(r).at(2);
  std::pair <int, int> d = curBlock->getCells().at(r).at(3);
  for(std::size_t i = 0; i < grid.size(); ++i) {
      for(std::size_t j = 0; j < grid.at(i).size(); ++j) {
          if (((int)j == base.first+a.first && 18-1-(int)i == base.second+a.second) ||
              ((int)j == base.first+b.first && 18-1-(int)i == base.second+b.second) ||
              ((int)j == base.first+c.first && 18-1-(int)i == base.second+c.second) ||
              ((int)j == base.first+d.first && 18-1-(int)i == base.second+d.second)) {
                  std::cout << "X";
          } else {
              std::cout << (int)boardModel_->getCell(j, i).first;
          }
      }
      std::cout << std::endl;
  }
}
