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

  // Increments after each move, used to uniquely ID a dropped block for Bonus calculation
  int timestamp_ = 0;
  // Maps timestamp value to a pair:
  // first: counter representing the number of squares belonging to the block left on grid_
  // second: level at which the block was dropped
  std::unordered_map<int, std::pair<int, int>> liveBlocks_;

  // Counts number of times you placed a block without clearing at least one row
  int nonClearStreak_ = 0;

  // 11x18 vector of chars representing cells. The char represents the Block type.
  std::vector<std::vector<std::pair<BlockType, int>>> grid_;

  // Pointer to the Block that the player currently has control over
  std::shared_ptr<GenericBlock> curBlock_;
  int curBlockLevel_;

  // Pointer to the Block that comes next
  std::shared_ptr<GenericBlock> nextBlock_;
  int nextBlockLevel_;

  // Pointer to the Hint block
  std::shared_ptr<GenericBlock> hintBlock_;

  int score_; // keep track of the score
  int hi_score_; // keep track of the highest score
  int level_; // keep track of the curent level
  bool isGameOver_ = false;

  // Vector of pointers to GenericLevel object, each level at corresponding index
  std::vector <std::shared_ptr<GenericLevel>> levelArray_;

public:
  // default constructor for the board model
  BoardModel();
  // constructor to initialize the flags
  BoardModel(int, std::string, int, bool);
  // destructor
  ~BoardModel();
  bool checkIfValidMove(int, int, int); // check if any of the 4 coordinates overlaps with a filled cell on the grid.
  // function to check if rows are completed
  void checkCompletedRows();
  void left(int, bool, bool); // handles the left command
  void right(int, bool, bool); // handles the right command
  void down(int, bool, bool); // handles the down command
  void clockwise(int, bool, bool); // handles the clockwise command
  void counterclockwise(int, bool, bool); // handles the counterclockwise command
  void drop(int); // handles the drop command
  void levelup(int); // handles the levelup command
  void leveldown(int); // handles the leveldown command
  void random(); // set random mode
  void I(int); // handles the I command
  void J(int); // handles the J command
  void L(int); // handles the L command
  void S(int); // handles the S command
  void Z(int); // handles the Z command
  void O(int); // handles the O command
  void T(int); // handles the T command
  void restart(); // handles the restart command
  void hint(); // handles the hint command
  void saveGame(std::string); // handles the save game command
  void loadGame(std::string); // function to load the game

  // Accessors and mutators
  int getGridX() const; // getter grid x constant
  int getGridY() const; // getter grid y constant
  std::vector <std::vector <std::pair<BlockType, int>>> getGrid() const; // getter for grid
  std::pair<BlockType, int> getCell(int, int) const; // getter for cell
  void setCell(int, int, std::pair<BlockType, int>); // setter for cell
  std::shared_ptr<GenericBlock> getCurBlock() const; // getter for the current block
  std::shared_ptr<GenericBlock> getNextBlock() const; // getter for the next block
  std::shared_ptr<GenericBlock> getHintBlock() const; // getter for the hint block
  void clearHintBlock(); //clear the hint block
  int getScore() const; // getter for the score
  void setScore(int); // setter for the score
  int getHiScore() const; // getter for the HI score
  void setHiScore(int); // setter for the HI score
  int getLevel() const; // getter for the level
  void setLevel(int); // setter for the level
  int getNonClearStreak() const; // getter for the non clear streak
  void setNonClearStreak(int); // setter for the non clear streak
  void setTimestamp(int); // setter for the time stamp
  void setBlockGenSequence(std::vector<BlockType>); // setter for the block generating sequence
  void setLevels(std::vector <std::shared_ptr<GenericLevel>>); // setter for the levels
  bool getIsGameOver() const; // getter for the game over flag
};

#endif // PROJECT_2_3_BOARDMODEL_H
