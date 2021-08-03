// TextDisplay.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_TEXTDISPLAY_H
#define PROJECT_2_3_TEXTDISPLAY_H
#include <iostream>
#include <memory>
#include "Observer.h"
#include <utility>
#include <unordered_map>
#include "BoardModel.h"

class BoardModel;

// used as the view presented to the user
class TextDisplay: public Observer{
private:
  std::weak_ptr<BoardModel> boardModel_; // the boardmodel is the subject this is observing
  std::unordered_map<BlockType, char> blockTypeToChar_; //mapping from type to char
  void printHeader(); // function to print the header message
  void printGrid(); // function to print the grid
  void printNextBlock(); // function to print messages about the next block
  void printGameOver(); // function to print the game over message

public:
  explicit TextDisplay(std::shared_ptr<BoardModel>); // constructor for initialization

  void update () override; //function for updating in observer

  std::shared_ptr<BoardModel> getBoardModel() const; // getter for the board model
};

#endif // PROJECT_2_3_TEXTDISPLAY_H
