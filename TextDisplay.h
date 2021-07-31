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
  BoardModel& boardModel_; // the boardmodel is the subject this is observing
  std::unordered_map<BlockType, char> blockTypeToChar_; //mapping from type to char
  void printHeader();
  void printGrid();
  void printNextBlock();

public:
  explicit TextDisplay(BoardModel&); // constructor for initialization
  ~TextDisplay() override; // destructor that cleans up the memory

  void update () override; //function for updating in observer
};

#endif // PROJECT_2_3_TEXTDISPLAY_H
