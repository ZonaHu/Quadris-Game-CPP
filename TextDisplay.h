// TextDisplay.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_TEXTDISPLAY_H
#define PROJECT_2_3_TEXTDISPLAY_H
#include <iostream>
#include <memory>
#include "Observer.h"

class BoardModel;

// used as the view presented to the user
class TextDisplay: public Observer{
private:
  std::shared_ptr<BoardModel> boardModel_; // the boardmodel pointer is the subject this is observing

public:
  TextDisplay(std::shared_ptr<BoardModel> boardModel); // constructor for initialization
  ~TextDisplay() override; // destructor that cleans up the memory

  void update (std::shared_ptr <Subject>) override; //function for updating in observer
};

#endif // PROJECT_2_3_TEXTDISPLAY_H
