// Controller.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "Controller.h"
#include "BoardModel.h"
#include <string>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <ctype.h>
#include <iostream>

Controller::Controller(std::shared_ptr <BoardModel> board) {
	boardModel_ = board;
	commandList_ = {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random", "sequence",
			"I", "J", "L", "S", "Z", "O", "T", "restart", "hint", "rename", "macro"}
	tempMacroName_ = "";
	macroInputFlag_ = false;
}

Controller::~Controller() {
	commandList_.clear();
	macroMap_.clear();
	tempMacroStore_.clear();
	tempMacroName_.clear();
}

bool Controller::parse(std::string input, std::string command) {
	bool flag = true;
	for (int i = 0; i < (int) input.length; i++) {
		if (input[i] != command[i]){
			flag = false;
			break;
		}
	}
	return flag;
}

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

void Controller::macro(std::vector <std::string> args) {
	// The first element of args should either be new, save, or exec
	if (args[0] == "new") {
		try {
			tempMacroName_ = args[1];
		} catch (const std::out_of_range &e) {
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
				execCommand(commandList_[cmdVec[i][1]] + " " + cmdVec[i][2], cmdVec[i][0]);
			}
		}
	} else {
		std::cout << "Please use a correct parameter with \"macro\". Valid parameters are: new, save, exec." << std::endl;
	}
}

void Controller::execCommand(std::string input, int multiplier) {
	if (multiplier == 0) {
		return;
	} else {
		if (macroInputFlag_) {
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
				if (commandList_[i] == cmd) {
					cmdNum = i;
					break;
				}
			}
			if (cmdNum == -1) {
				multiplier = 0;
			}
			std::tuple<int, int, std::string> line = (multiplier, cmdNum, args);
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
			}
			if (parse(cmdStart, commandList_[0])) {
				boardModel_->left(multiplier);
			} else if (parse(cmdStart, commandList_[1])) {
				boardModel_->right(multiplier);
			} else if (parse(cmdStart, commandList_[2])) {
				boardModel_->down(multiplier);
			} else if (parse(cmdStart, commandList_[3])) {
				boardModel_->clockwise(multiplier);
			} else if (parse(cmdStart, commandList_[4])) {
				boardModel_->counterclockwise(multiplier) ;
			} else if (parse(cmdStart, commandList_[5])) {
				boardModel_->drop(multiplier);
			} else if (parse(cmdStart, commandList_[6])) {
				boardModel_->levelup(multiplier);
			} else if (parse(cmdStart, commandList_[7])) {
				boardModel_->leveldown(multiplier);
			} else if (parse(cmdStart, commandList_[8]) && (int) cmdArgs.size() == 1) {
				boardModel_->norandom(cmdArgs[0]);
			} else if (parse(cmdStart, commandList_[9])) {
				boardModel_->random();
			} else if (parse(cmdStart, commandList_[10]) && (int) cmdArgs.size() == 1) {
				boardModel_->sequence(cmdArgs[0]);
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
			} else if (parse(cmdStart, commandList_[20])) {
				rename(cmdArgs);
			} else if (parse(cmdStart, commandList_[21])) {
				macro(cmdArgs);
			} else {
				std::cout << "Please input a correct command." << std::endl;
			}
		}
	}
}

void Controller::extractMultiplier(std::string input) {
	int multiplier = 1;
	std::string command = "";
	std::string multWord = "";
	int cmdStart = 0;
	for (int i = 0; i < (int) input.length(); i++) {
		if (std::isDigit(input[i])) {
			multWord.append(input[i]);
		} else {
			cmdStart = i;
			break;
		}
	}
	if (!multWord.empty()) {
		multiplier = std::atoi(multWord);
	}
	command = input.substr(cmdStart);
	execCommand(command, multiplier);
}

std::istream &operator>>(std::istream &in, Controller &control) {
	std::string input;
	in >> input;
	control->extractMultiplier(input);
	return in;
}
