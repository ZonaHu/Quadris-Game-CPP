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

class GenericLevel;

class BoardModel: public Subject {
  // does not communicate with the user at all
  // notify the observers when appropriate
private:
  // Counts number of times you placed a block without clearing at least one row
  int nonClearStreak_;

  // 11x18 vector of chars representing cells. The char represents the Block type.
  std::vector<std::vector <char>> grid_;

  // Pointer to the Block that the player currently has control over
  GenericBlock* curBlock_;

  // Pointer to the Block that comes next
  GenericBlock* nextBlock_;

  int score_; // keep track of the score
  int hi_score_; // keep track of the highest score
  int level_; // keep track of the curent level

  // Vector of pointers to GenericLevel object, each level at corresponding index
  std::vector <GenericLevel*> levelArray_;

public:
  BoardModel();
  ~BoardModel();
  bool checkIfValidMove(int, int, int); // check if any of the 4 coordinates overlaps with a filled cell on the grid.
  void checkCompletedRows();
  void calcScore();
  void left(int);
  void right(int);
  void down(int);
  void clockwise(int);
  void counterclockwise(int);
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

  // getters
  std::vector <std::vector <char>> getGrid() const;
  GenericBlock* getCurBlock() const;
  GenericBlock* getNextBlock() const;
  int getScore() const;
  int getHiScore() const;
  int getLevel() const;
  // getter for nonClearStreak_
  int getNonClearStreak() const;
  // setter for nonClearStreak_
  void setNonClearStreak();
};

#endif // PROJECT_2_3_BOARDMODEL_H
