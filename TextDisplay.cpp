// File: TextDisplay.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "TextDisplay.h"
#include <utility>

TextDisplay::TextDisplay(std::shared_ptr<BoardModel> boardModel){
  boardModel_ = boardModel;
}

TextDisplay::~TextDisplay() {
  //call unsubscribe in the destructor
  boardModel_->unsubscribe(this);
}

void TextDisplay::update() {
  // this function prints out all
  std::cout << "Level:        " << boardModel_.getLevel() << std::endl;
  std::cout << "Score:        " << boardModel_.getScore() << std::endl;
  std::cout << "Hi Score:     " << boardModel_.getHiScore() << std::endl;
  std::cout << "-----------------" << std::endl;
  int count = 1; // count denotes the current line number
  while (count < 19){
    if (count>=1&&count<=9){
      std::cout << " " << count << "   "; // 1 digit numbers will have an extra space at the beginning fot format
    }
    else{
      std::cout << count << "   "; // 2 digit numbers
    }
    // print the rest of things in the same line corresponding to count





    count++; // increment the current line number
  }

}


