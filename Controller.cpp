// Controller.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "Controller.h"
#include "BoardModel.h"
#include "GenericBlock.h"
#include <string>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>

// Constructor (boolean flag for enabling bonus features renaming and macro)
Controller::Controller(bool enableBonus) {
  commandList_ = {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random", "sequence",
                  "I", "J", "L", "S", "Z", "O", "T", "restart", "hint", "rename", "macro", "save", "load"};
  tempMacroName_ = "";
  macroInputFlag_ = false;
  enableBonus_ = enableBonus;
}

// Destructor (we need to clear all vectors associated with the Controller object)
Controller::~Controller() {
  commandList_.clear();
  macroMap_.clear();
  tempMacroStore_.clear();
  tempMacroName_.clear();
}

// Setting the private variable boardModel_.
void Controller::setBoard(std::shared_ptr <BoardModel> board) {
  boardModel_ = board;
}

// For comparing command input against current valid command names.
bool Controller::parse(std::string input, std::string command) {
  if (input.size() == 0) return false;

  bool flag = true;
  for (int i = 0; i < (int) input.length(); i++) {
    if (input[i] != command[i]){
      flag = false;
      break;
    }
  }
  return flag;
}
// Updates the command vector (which contains existing command names) with a new valid command name.
void Controller::rename(std::vector <std::string> args) {
  // Where the original name is args[0], and the new name is args[1]
  std::vector <std::string>::iterator it;
  std::vector <std::string>::iterator it2;
  it = std::find(commandList_.begin(), commandList_.end(), args[0]);
  it2 = std::find(commandList_.begin(), commandList_.end(), args[1]);
  if (it != commandList_.end() && it2 == commandList_.end()) {
    *it = args[1];
  } else {
    std::cout << "When renaming, please first specify the name of a command in use, then a new name that is not the name of anything else already." << std::endl;
  }
}
/* Handles macro arguments such as new, save, and exec.
 * - new: we enter the macro state of input; so that commands that are entered into the console/command line are not executed immediately.
 * - save: at the end of inputting commands for a new macro, we run "macro save" to properly store the macro and go back to normal state.
 * - exec: "macro exec" executes all the commands sequentially in a given macro.
 */

void Controller::macro(std::vector <std::string> args) {
  // The first element of args should either be new, save, or exec
  if (args[0] == "new") {
    if ((int)args.size() >= 2) {
      tempMacroName_ = args[1];
    } else {
      std::cout << "Please provide a name for the new macro." << std::endl;
    }
    if (!tempMacroName_.empty()){
      macroInputFlag_ = true;
      std::cout << "Input a command on every new line. You can save your macro with \"macro save\"." << std::endl;
    }
  } else if (args[0] == "save") {
    if (macroInputFlag_) {
      macroMap_.insert(std::pair<std::string, std::vector<std::tuple<int, int, std::string>>>(tempMacroName_, tempMacroStore_));
      tempMacroName_.clear();
      tempMacroStore_.clear();
      macroInputFlag_ = false;
    } else {
      std::cout << "You can only save a macro if you were inputting commands for one in the first place!" << std::endl;
    }
  } else if (args[0] == "exec") {
    std::vector<std::tuple<int, int, std::string>> cmdVec;
    try {
      cmdVec = macroMap_.at(args[1]);
    } catch (const std::out_of_range &e) {
      std::cout << "Please specify a valid macro name." << std::endl;
    }
    if (!cmdVec.empty()) {
      for (int i = 0; i < (int) cmdVec.size(); i++) {
        execCommand(commandList_[std::get<1>(cmdVec[i])] + " " + std::get<2>(cmdVec[i]), std::get<0>(cmdVec[i]));
      }
    }
  } else {
    std::cout << "Please use a correct parameter with \"macro\". Valid parameters are: new, save, exec." << std::endl;
  }
}

// For reading in from a file that contains commands to execute.
void Controller::sequence(std::string fileName) {
  std::ifstream file (fileName);
  std::string line = "";
  if (file.is_open()) {
    while (std::getline(file, line)) {
      extractMultiplier(line);
    }
    file.close();
  } else {
    std::cout << "Unable to open file (for sequence command)." << std::endl;
  }
}
// For reading in from a file to get the blocks we need for some commands.
std::vector <BlockType> Controller::blockSequenceSource(std::string fileName) {
  std::ifstream file (fileName);
  std::string line = "";
  std::vector <BlockType> blockList;
  std::string block[8] = {"I", "J", "L", "O", "S", "Z", "T", "*"};
  if (file.is_open()) {
    while (std::getline(file, line)) {
      size_t pos = 0;
      int index = 0;
      while ((pos = line.find(" ")) != std::string::npos) {
        std::string token = line.substr(0, pos);
        for (int i = 0; i < 8; i++){
          if (block[i] == token){
            index = i;
            break;
          }
        }
        blockList.push_back(static_cast<BlockType>(index));
        line.erase(0, pos + 1);
      }
      for (int i = 0; i < 8; i++){
        if (block[i] == line){
          index = i;
          break;
        }
      }
      blockList.push_back(static_cast<BlockType>(index));
    }
    file.close();
  } else {
    std::cout << "Unable to open file (for norandom command/initializing level 0)." << std::endl;
  }
  return blockList;
}
// After recognizing a valid command through parse(), executes it's relevant function.
void Controller::execCommand(std::string input, int multiplier) {
  if (multiplier == 0) {
    return;
  } else {
    if (macroInputFlag_ && input.compare("macro save") && enableBonus_) {
      // This section is for taking the commands inputted while in macro mode instead of executing them (by calling their functions).
      int cmdNum = -1;
      std::string cmd = "";
      std::string args = "";
      size_t cmdPos = 0;
      cmdPos = input.find(" ");
      if (cmdPos != std::string::npos) {
        cmd = input.substr(0, cmdPos);
        input.erase(0, cmdPos + 1);
        args = input;
      } else {
        cmd = input;
      }
      for (int i = 0; i < (int) commandList_.size(); i++) {
        if (parse(cmd, commandList_[i])) {
          cmdNum = i;
          break;
        }
      }
      if (cmdNum == -1) {
        multiplier = 0;
      }
      std::tuple<int, int, std::string> line = (std::make_tuple(multiplier, cmdNum, args));
      tempMacroStore_.push_back(line);
    } else {
      std::string cmdStart = "";
      std::vector <std::string> cmdArgs;
      size_t pos = 0;
      while ((pos = input.find(" ")) != std::string::npos) {
        std::string token = input.substr(0, pos);
        if (cmdStart.empty()) {
          cmdStart = token;
        } else {
          cmdArgs.push_back(token);
        }
        input.erase(0, pos + 1);
      }
      if (cmdStart.empty()){
        cmdStart = input;
      } else {
        cmdArgs.push_back(input);
      }
      boardModel_->clearHintBlock();
      if (parse(cmdStart, commandList_[0])) {
        boardModel_->left(multiplier, true, true);
      } else if (parse(cmdStart, commandList_[1])) {
        boardModel_->right(multiplier, true, true);
      } else if (parse(cmdStart, commandList_[2])) {
        boardModel_->down(multiplier, true, true);
      } else if (parse(cmdStart, commandList_[3])) {
        boardModel_->clockwise(multiplier, true, true);
      } else if (parse(cmdStart, commandList_[4])) {
        boardModel_->counterclockwise(multiplier, true, true) ;
      } else if (parse(cmdStart, commandList_[5])) {
        boardModel_->drop(multiplier);
      } else if (parse(cmdStart, commandList_[6])) {
        boardModel_->levelup(multiplier);
      } else if (parse(cmdStart, commandList_[7])) {
        boardModel_->leveldown(multiplier);
      } else if (parse(cmdStart, commandList_[8]) && (int) cmdArgs.size() == 1) {
        boardModel_->setBlockGenSequence(blockSequenceSource(cmdArgs[0]));
      } else if (parse(cmdStart, commandList_[9])) {
        boardModel_->random();
      } else if (parse(cmdStart, commandList_[10]) && (int) cmdArgs.size() == 1) {
        sequence(cmdArgs[0]);
      } else if (parse(cmdStart, commandList_[11])) {
        boardModel_->I(multiplier);
      } else if (parse(cmdStart, commandList_[12])) {
        boardModel_->J(multiplier);
      } else if (parse(cmdStart, commandList_[13])) {
        boardModel_->L(multiplier);
      } else if (parse(cmdStart, commandList_[14])) {
        boardModel_->S(multiplier);
      } else if (parse(cmdStart, commandList_[15])) {
        boardModel_->Z(multiplier);
      } else if (parse(cmdStart, commandList_[16])) {
        boardModel_->O(multiplier);
      } else if (parse(cmdStart, commandList_[17])) {
        boardModel_->T(multiplier);
      } else if (parse(cmdStart, commandList_[18])) {
        boardModel_->restart();
      } else if (parse(cmdStart, commandList_[19])) {
        boardModel_->hint();
      } else if (parse(cmdStart, commandList_[20]) && enableBonus_) {
        rename(cmdArgs);
      } else if (parse(cmdStart, commandList_[21]) && enableBonus_) {
        macro(cmdArgs);
      } else if (parse(cmdStart, commandList_[22]) && enableBonus_ && (int) cmdArgs.size() == 1) {
        boardModel_->saveGame(cmdArgs[0]);
      } else if (parse(cmdStart, commandList_[23]) && enableBonus_ && (int) cmdArgs.size() == 1) {
        boardModel_->loadGame(cmdArgs[0]);
      } else {
        std::cout << "Please input a correct command." << std::endl;
      }
    }
  }
}

// For getting the number of times a specific command needs to run.
void Controller::extractMultiplier(std::string input) {
  int multiplier = 1;
  std::string command = "";
  std::string multWord = "";
  int cmdStart = 0;
  for (int i = 0; i < (int) input.length(); i++) {
    if (std::isdigit(input[i])) {
      multWord.append(input.substr(i,i+1));
    } else {
      cmdStart = i;
      break;
    }
  }
  if (!multWord.empty()) {
    multiplier = std::atoi(multWord.c_str());
  }
  command = input.substr(cmdStart);
  execCommand(command, multiplier);
}

//  Pass cin input to extractMultiplier().
std::istream &operator>>(std::istream &in, Controller &control) {
  std::string input;
  std::getline(in, input);
  control.extractMultiplier(input);
  return in;
}
