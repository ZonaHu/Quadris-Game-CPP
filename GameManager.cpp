// GameManager.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "GameManager.h"

/* Create instance of BoardModel passing the following to the constructor (seed, scriptFile, startLevel).
Create instance of  appropriate Observer derived classes based on value of isTextOnly; subscribe them to the BoardModel.
Create an instance of Controller passing BoardModel to the constructor.
Begin an infinite while loop that reads user input from cin into the Controller input overload.*/

GameManager::GameManager() {
  // TODO: initialize all private members
    BoardModel_ = std::make_shared<BoardModel>();




}

//  Starts an infinite game while loop that constantly reads input to the Controller.
//  (game ends on reading EOF)
void GameManager::start() {
  // TODO: Initializes the game.
}
