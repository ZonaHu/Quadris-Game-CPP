// GenericLevel.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "GenericLevel.h"

// initialize all data members
// gets called in the board model class, the parameter will be passes in
GenericLevel::GenericLevel(const std::weak_ptr<BoardModel> p) {
  // constructor
   boardModel_ = p;
}

std::shared_ptr <BoardModel> GenericLevel::getBoardModel() const {
  return boardModel_.lock(); //getter for the board model
}

void GenericLevel::setBlockGenSequence(std::vector<BlockType> seq) {
  blockSeq_ = seq; //set the vector
}

void GenericLevel::setIsNonRandom(bool isNonRandom) {
  isNonRandom_ = isNonRandom; // set the is non-random flag
}