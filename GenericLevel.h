// GenericLevel.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.


#ifndef PROJECT_2_3_GENERICLEVEL_H
#define PROJECT_2_3_GENERICLEVEL_H
#include "BoardModel.h"
#include <memory>
#include "GenericBlock.h"
#include <random>
#include <vector>

class BoardModel;

class GenericLevel {
protected:
  // a shared Pointer to BoardModel object
  std::shared_ptr <BoardModel> boardModel_;
  // Sequence of blocks for levels that have a "non-random" mode
  std::vector<BlockType> blockSeq_;
  bool isNonRandom_;

public:
  GenericLevel(){}; // default constructor
  GenericLevel(const std::shared_ptr<BoardModel> p); // constructor
  virtual ~GenericLevel(){}; // default destructor

  // Determines next block based on probability or sequence file, depending on the level
  virtual std::shared_ptr <GenericBlock> generateNextBlock() = 0;

  // Gets called after every move in BoardModel
  virtual void postMoveOperation() = 0;

  // Gets called after every drop() in BoardModel
  virtual void postDropOperation() = 0;

  void setBlockGenSequence(std::vector<BlockType>);
  void setIsNonRandom(bool);
};

#endif // PROJECT_2_3_GENERICLEVEL_H
