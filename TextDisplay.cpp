// File: TextDisplay.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "TextDisplay.h"

TextDisplay::TextDisplay(std::shared_ptr<BoardModel> boardModel):boardModel_{boardModel}{
  // constructor to initialize the private data members
  blockTypeToChar_[BlockType::I_BLOCK] = 'I';
  blockTypeToChar_[BlockType::J_BLOCK] = 'J';
  blockTypeToChar_[BlockType::L_BLOCK] = 'L';
  blockTypeToChar_[BlockType::O_BLOCK] = 'O';
  blockTypeToChar_[BlockType::S_BLOCK] = 'S';
  blockTypeToChar_[BlockType::Z_BLOCK] = 'Z';
  blockTypeToChar_[BlockType::T_BLOCK] = 'T';
  blockTypeToChar_[BlockType::STAR_BLOCK] = '*';
  blockTypeToChar_[BlockType::EMPTY] = ' ';
  update();
}

std::shared_ptr<BoardModel> TextDisplay::getBoardModel() const {
  // getter
  return boardModel_.lock();
}

void TextDisplay::printHeader() {
  // function to print the header message
  std::cout << "Start Text-Based Display" << std::endl;
  std::cout << "     Level:      " << getBoardModel()->getLevel() << std::endl;
  std::cout << "     Score:      " << getBoardModel()->getScore() << std::endl;
  std::cout << "     Hi-Score:   " << getBoardModel()->getHiScore() << std::endl;
  std::cout << "     -------------" << std::endl;
}

void TextDisplay::printGrid() {
  std::vector <std::vector <std::pair<BlockType, int>>> curGrid = getBoardModel()->getGrid(); // the current grid

  // Get cell information of current block
  std::shared_ptr<GenericBlock> curBlock = getBoardModel()->getCurBlock();
  int r = curBlock->getRotation();
  std::pair <int, int> baseCoords = curBlock->getCoords();
  std::pair <int, int> cell0 = curBlock->getCells().at(r).at(0);
  std::pair <int, int> cell1 = curBlock->getCells().at(r).at(1);
  std::pair <int, int> cell2 = curBlock->getCells().at(r).at(2);
  std::pair <int, int> cell3 = curBlock->getCells().at(r).at(3);

  // Get cell information of hint block, if it exists
  std::shared_ptr<GenericBlock> hintBlock = getBoardModel()->getHintBlock();
  int hintR = hintBlock != nullptr ? hintBlock->getRotation() : -1;
  std::pair <int, int> hintBaseCoords = hintBlock != nullptr ? hintBlock->getCoords() : std::make_pair(-1,-1);
  std::pair <int, int> hintCell0 = hintBlock != nullptr ? hintBlock->getCells().at(hintR).at(0) : std::make_pair(-1,-1);
  std::pair <int, int> hintCell1 = hintBlock != nullptr ? hintBlock->getCells().at(hintR).at(1) : std::make_pair(-1,-1);
  std::pair <int, int> hintCell2 = hintBlock != nullptr ? hintBlock->getCells().at(hintR).at(2) : std::make_pair(-1,-1);
  std::pair <int, int> hintCell3 = hintBlock != nullptr ? hintBlock->getCells().at(hintR).at(3) : std::make_pair(-1,-1);

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
      if (((int)j == baseCoords.first+cell0.first && 18-1-(int)i == baseCoords.second+cell0.second) ||
          ((int)j == baseCoords.first+cell1.first && 18-1-(int)i == baseCoords.second+cell1.second) ||
          ((int)j == baseCoords.first+cell2.first && 18-1-(int)i == baseCoords.second+cell2.second) ||
          ((int)j == baseCoords.first+cell3.first && 18-1-(int)i == baseCoords.second+cell3.second)) {
        // print the current block's cell
        std::cout << blockTypeToChar_.at(curBlock->getType());
      } else if (((int)j == hintBaseCoords.first+hintCell0.first && 18-1-(int)i == hintBaseCoords.second+hintCell0.second) ||
                 ((int)j == hintBaseCoords.first+hintCell1.first && 18-1-(int)i == hintBaseCoords.second+hintCell1.second) ||
                 ((int)j == hintBaseCoords.first+hintCell2.first && 18-1-(int)i == hintBaseCoords.second+hintCell2.second) ||
                 ((int)j == hintBaseCoords.first+hintCell3.first && 18-1-(int)i == hintBaseCoords.second+hintCell3.second)) {
        // Print out hint character
        std::cout << "?";
      } else {
        // print the other blocks on the grid
        std::cout << blockTypeToChar_.at(getBoardModel()->getCell(j, 18-1-i).first);
      }
    }
    std::cout << std::endl;
  }
}

void TextDisplay::printNextBlock() {
  // function to print the next block
  std::cout << "     -------------" << std::endl;
  std::cout << "     Next Block:      " << std::endl;
  std::shared_ptr <GenericBlock> nextBlock = getBoardModel()->getNextBlock(); // get the next block we want
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
      else {
        std::cout << " "; // else it should be empty
      }
    }
    std::cout << std::endl;
  }
}

void TextDisplay::printGameOver() {
  // function to print the game over message
  std::cout << " _____ _____ _____ _____    _____ _____ _____ _____  \n"
               "|   __|  _  |     |   __|  |     |  |  |   __| __  | \n"
               "|  |  |     | | | |   __|  |  |  |  |  |   __|    -| \n"
               "|_____|__|__|_|_|_|_____|  |_____|\\___/|_____|__|__|\n" << std::endl;
  std::cout << "YOUR SCORE: " << getBoardModel()->getScore() << std::endl;
  std::cout << "HI SCORE: " << getBoardModel()->getHiScore() << std::endl;
  std::cout << "Enter [restart] to play again!" << std::endl;
}

void TextDisplay::update() {
  // this function prints out all messages
  printHeader();
  printGrid();
  printNextBlock();
  if (getBoardModel()->getIsGameOver()) {
    printGameOver();
  }
}