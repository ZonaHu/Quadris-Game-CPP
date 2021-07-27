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


}


