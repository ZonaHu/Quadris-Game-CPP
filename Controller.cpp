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
#include <ctype.h>
#include <iostream>
#include <fstream>

Controller::Controller(bool enableBonus) {
	commandList_ = {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random", "sequence",
			"I", "J", "L", "S", "Z", "O", "T", "restart", "hint", "rename", "macro", "save"};
	tempMacroName_ = "";
	macroInputFlag_ = false;
	enableBonus_ = enableBonus;
}

Controller::~Controller() {
	commandList_.clear();
	macroMap_.clear();
	tempMacroStore_.clear();
	tempMacroName_.clear();
}

void Controller::setBoard(std::shared_ptr <BoardModel> board) {
	boardModel_ = board;
}

bool Controller::parse(std::string input, std::string command) {
	bool flag = true;
	for (int i = 0; i < (int) input.length(); i++) {
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

void Controller::execCommand(std::string input, int multiplier) {
	if (multiplier == 0) {
		return;
	} else {
		if (macroInputFlag_ && input.compare("macro save") && enableBonus_) {
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
				boardModel_->I();
			} else if (parse(cmdStart, commandList_[12])) {
				boardModel_->J();
			} else if (parse(cmdStart, commandList_[13])) {
				boardModel_->L();
			} else if (parse(cmdStart, commandList_[14])) {
				boardModel_->S();
			} else if (parse(cmdStart, commandList_[15])) {
				boardModel_->Z();
			} else if (parse(cmdStart, commandList_[16])) {
				boardModel_->O();
			} else if (parse(cmdStart, commandList_[17])) {
				boardModel_->T();
			} else if (parse(cmdStart, commandList_[18])) {
				boardModel_->restart();
			} else if (parse(cmdStart, commandList_[19])) {
				boardModel_->hint();
			} else if (parse(cmdStart, commandList_[20]) && enableBonus_) {
				rename(cmdArgs);
			} else if (parse(cmdStart, commandList_[21]) && enableBonus_) {
				macro(cmdArgs);
			} else if (parse(cmdStart, commandList_[22]) && enableBonus_) {
				boardModel_->saveGame();
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

std::istream &operator>>(std::istream &in, Controller &control) {
	std::string input;
	std::getline(in, input);
	control.extractMultiplier(input);
	return in;
}
