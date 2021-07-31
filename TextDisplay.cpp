// File: TextDisplay.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "TextDisplay.h"

TextDisplay::TextDisplay(std::shared_ptr<BoardModel> boardModel){
  // constructor to initialize the private data members
  boardModel_ = boardModel;
  blockTypeToChar_[BlockType::I_BLOCK] = 'I';
  blockTypeToChar_[BlockType::J_BLOCK] = 'J';
  blockTypeToChar_[BlockType::L_BLOCK] = 'L';
  blockTypeToChar_[BlockType::O_BLOCK] = 'O';
  blockTypeToChar_[BlockType::S_BLOCK] = 'S';
  blockTypeToChar_[BlockType::Z_BLOCK] = 'Z';
  blockTypeToChar_[BlockType::T_BLOCK] = 'T';
  blockTypeToChar_[BlockType::STAR_BLOCK] = '*';
  blockTypeToChar_[BlockType::EMPTY] = ' ';
}

TextDisplay::~TextDisplay() {
  //call unsubscribe in the destructor
  boardModel_->unsubscribe(this);
}

void TextDisplay::printHeader() {
  std::cout << "     Start Text-based Display" << std::endl;
  std::cout << "     Level:        " << boardModel_->getLevel() << std::endl;
  std::cout << "     Score:        " << boardModel_->getScore() << std::endl;
  std::cout << "     Hi-Score:     " << boardModel_->getHiScore() << std::endl;
  std::cout << "     -----------------" << std::endl;
}

void TextDisplay::printGrid() {
  std::vector <std::vector <std::pair<BlockType, int>>> curGrid = boardModel_->getGrid(); // the current grid
  std::shared_ptr<GenericBlock> curBlock = boardModel_->getCurBlock(); // the current block
  int r = curBlock->getRotation();
  std::pair <int, int> base = curBlock->getCoords();
  std::pair <int, int> a = curBlock->getCells().at(r).at(0);
  std::pair <int, int> b = curBlock->getCells().at(r).at(1);
  std::pair <int, int> c = curBlock->getCells().at(r).at(2);
  std::pair <int, int> d = curBlock->getCells().at(r).at(3);
  for(std::size_t i = 0; i < curGrid.size(); ++i) {
    int count = i+1; // count denotes the current line number
    if (count >= 1 && count <= 9){
      std::cout << " " << count << "   "; // 1 digit numbers will have an extra space at the beginning fot format
    }
    else{
      std::cout << count << "   "; // 2 digit numbers
    }
    for(std::size_t j = 0; j < curGrid.at(i).size(); ++j){
      // print the rest of things in the same line corresponding to count
      if (((int)j == base.first+a.first && 18-1-(int)i == base.second+a.second) ||
          ((int)j == base.first+b.first && 18-1-(int)i == base.second+b.second) ||
          ((int)j == base.first+c.first && 18-1-(int)i == base.second+c.second) ||
          ((int)j == base.first+d.first && 18-1-(int)i == base.second+d.second)) {
        // print the current block
        std::cout << blockTypeToChar_.at(curBlock->getType());
      } else {
        // print the other blocks on the grid
        std::cout << blockTypeToChar_.at(boardModel_ -> getCell(j, 18-1-i).first);
      }
    }
    std::cout << std::endl;
  }
}

void TextDisplay::printNextBlock() {
  // function to print the next block
  std::cout << "     -----------------" << std::endl;
  std::cout << "     Next Block:      " << std::endl;
  std::shared_ptr <GenericBlock> nextBlock = boardModel_->getNextBlock(); // get the next block we want
  // get the coordinates for each letter's position
  std::pair <int, int> a = nextBlock->getCells().at(0).at(0);
  std::pair <int, int> b = nextBlock->getCells().at(0).at(1);
  std::pair <int, int> c = nextBlock->getCells().at(0).at(2);
  std::pair <int, int> d = nextBlock->getCells().at(0).at(3);
  for (int j = 1; j >= 0; j--){ // the original block has 2 rows and 4 columns
    // print the current row
    std::cout << "     "; // leading spaces
    for (int i = 0; i < 4; i++){
      if ((a.second == j && a.first == i)
          || (b.second == j && b.first == i)
          || (c.second == j && c.first == i)
          || (d.second == j && d.first == i)){ // if any coordinate matches
        std::cout << blockTypeToChar_.at(nextBlock->getType()); // print the current type
      }
      else{
        std::cout << " "; // else it should be empty
      }
    }
    std::cout << std::endl;
  }
}

void TextDisplay::update() {
  // this function prints out all
  printHeader();
  printGrid();
  printNextBlock();
}