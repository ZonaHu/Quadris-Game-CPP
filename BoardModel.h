// BoardModel.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_BOARDMODEL_H
#define PROJECT_2_3_BOARDMODEL_H
#include <vector>
#include "Subject.h"
#include "GenericBlock.h"
#include "GenericLevel.h"
#include <string>
#include <unordered_map>
#include <memory>

class GenericLevel;

class BoardModel: public Subject {
  // does not communicate with the user at all
  // notify the observers when appropriate
private:
  int gridX_ = 11;
  int gridY_ = 18;

  int timestamp_ = 0;
  std::unordered_map<int, std::pair<int, int>> liveBlocks_;

  // Counts number of times you placed a block without clearing at least one row
  int nonClearStreak_ = 0;

  // 11x18 vector of chars representing cells. The char represents the Block type.
  std::vector<std::vector<std::pair<BlockType, int>>> grid_;

  // Pointer to the Block that the player currently has control over
  std::shared_ptr<GenericBlock> curBlock_;

  // Pointer to the Block that comes next
  std::shared_ptr<GenericBlock> nextBlock_;

  // Pointer to the Hint block
  std::shared_ptr<GenericBlock> hintBlock_;

  int score_; // keep track of the score
  int hi_score_; // keep track of the highest score
  int level_; // keep track of the curent level
  bool isGameOver_ = false;

  // Vector of pointers to GenericLevel object, each level at corresponding index
  std::vector <std::shared_ptr<GenericLevel>> levelArray_;

public:
  BoardModel();
  BoardModel(int, std::string, int, bool);
  ~BoardModel();
  bool checkIfValidMove(int, int, int); // check if any of the 4 coordinates overlaps with a filled cell on the grid.
  void checkCompletedRows();
  void calcScore();
  void left(int, bool, bool);
  void right(int, bool, bool);
  void down(int, bool, bool);
  void clockwise(int, bool, bool);
  void counterclockwise(int, bool, bool);
  void drop(int);
  void levelup(int);
  void leveldown(int);
  void random();
  void I();
  void J();
  void L();
  void S();
  void Z();
  void O();
  void T();
  void restart();
  void hint();

  // Accessors and mutators
  std::vector <std::vector <std::pair<BlockType, int>>> getGrid() const;
  std::pair<BlockType, int> getCell(int, int) const;
  void setCell(int, int, std::pair<BlockType, int>);
  std::shared_ptr<GenericBlock> getCurBlock() const;
  std::shared_ptr<GenericBlock> getNextBlock() const;
  std::shared_ptr<GenericBlock> getHintBlock() const;
  void clearHintBlock();
  int getScore() const;
  int getHiScore() const;
  int getLevel() const;
  int getNonClearStreak() const;
  void setNonClearStreak(int);
  void setBlockGenSequence(std::vector<BlockType>);
  void setLevels(std::vector <std::shared_ptr<GenericLevel>>);
};

#endif // PROJECT_2_3_BOARDMODEL_H
