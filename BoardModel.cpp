// BoardModel.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "BoardModel.h"
#include <utility>
#include <cmath>
#include <fstream>
#include <cstdlib>

BoardModel::BoardModel() {
    // default constructor for the board model
    std::vector<std::vector<std::pair<BlockType, int>>> grid(gridY_, std::vector <std::pair<BlockType, int>> (gridX_, std::make_pair(BlockType::EMPTY, 0)));
    grid_ = grid;
}

BoardModel::BoardModel(int seed, std::string scriptFile, int startLevel, bool enableBonus) {
    // constructor to initialize the flags
    std::vector<std::vector<std::pair<BlockType, int>>> grid(gridY_, std::vector <std::pair<BlockType, int>> (gridX_, std::make_pair(BlockType::EMPTY, 0)));
    grid_ = grid;
    score_ = 0;
    hi_score_ = 0;
    level_ = startLevel;

    // Default blocks for until the levels are instantiated in setBlockGenSequence()
    curBlock_ = std::make_shared<IBlock>();
    nextBlock_ = std::make_shared<IBlock>();
}

BoardModel::~BoardModel() {}

void BoardModel::setLevels(std::vector <std::shared_ptr<GenericLevel>> levelArray) {
    // function to set levels
    levelArray_ = levelArray;
    curBlock_ = levelArray_.at(level_)->generateNextBlock(); // update current block
    nextBlock_ = levelArray_.at(level_)->generateNextBlock(); // update current block
    curBlockLevel_ = level_;
    nextBlockLevel_ = level_;
}

// Sets the block sequence for the current level
void BoardModel::setBlockGenSequence(std::vector<BlockType> seq) {
    if (seq.size() > 0) {
        levelArray_.at(level_)->setBlockGenSequence(seq);
        levelArray_.at(level_)->setIsNonRandom(true); // the non random flag should be true when setting the sequence ourselves
        curBlock_ = levelArray_.at(level_)->generateNextBlock(); // update current block
        nextBlock_ = levelArray_.at(level_)->generateNextBlock(); // update current block
        curBlockLevel_ = level_;
        nextBlockLevel_ = level_;
    }
}

// function to return the member gridX
int BoardModel::getGridX() const { return gridX_; }

// function to return the member gridY
int BoardModel::getGridY() const { return gridY_; }

std::vector <std::vector <std::pair<BlockType, int>>> BoardModel::getGrid() const { return grid_; }

// Transforms Cartesian coords to indices in grid_ vector
// i.e. (0,0) is bottom left corner of grid
std::pair<BlockType, int> BoardModel::getCell(int x, int y) const {
    return grid_.at(gridY_-1-y).at(x);
}

// setter for the cell
void BoardModel::setCell(int x, int y, std::pair<BlockType, int> data) {
    grid_.at(gridY_-1-y).at(x) = data;
}

// getter for the current block
std::shared_ptr<GenericBlock> BoardModel::getCurBlock() const { return curBlock_; }

// getter for the next block
std::shared_ptr<GenericBlock> BoardModel::getNextBlock() const { return nextBlock_; }

// getter for the hint block
std::shared_ptr<GenericBlock> BoardModel::getHintBlock() const { return hintBlock_; }

// clear the hint block
void BoardModel::clearHintBlock() { hintBlock_ = nullptr; }

// getter for the score
int BoardModel::getScore() const { return score_; }

// setter for the score
void BoardModel::setScore(int score) { score_ = score; }

// getter for HI score
int BoardModel::getHiScore() const { return hi_score_; }

// setter for HI score
void BoardModel::setHiScore(int hi_score) { hi_score_ = hi_score; }

// getter for the level
int BoardModel::getLevel() const { return level_; }

// setter for the level
void BoardModel::setLevel(int level) { level_ = level; }

// getter for the current non clear streak
int BoardModel::getNonClearStreak() const { return nonClearStreak_; }

// getter for the game over flag
bool BoardModel::getIsGameOver() const { return isGameOver_; }

// setter for the non clear streak
void BoardModel::setNonClearStreak(int n) { nonClearStreak_ = n; }

// setter for the time stamp
void BoardModel::setTimestamp(int t) { timestamp_ = t; }

// function to check if a move is valid
bool BoardModel::checkIfValidMove(int x, int y, int r) {
    // Get the cells of curBlock_ that correspond to rotation r
    std::vector<std::pair<int, int>> cells = curBlock_->getCells().at(r);

    // Iterate through the 4 squares of the block and check that they are in valid cells
    for(std::size_t i = 0; i < cells.size(); ++i) {
        // Calculate absolute coordinates on grid_
        int cellX = x+cells[i].first;
        int cellY = y+cells[i].second;
        // Out of bounds check
        if (cellX < 0 || cellX > gridX_ - 1 || cellY < 0 || cellY > gridY_ - 1) {
            return false;
        } 
        // Non-empty cell check
        if (getCell(cellX, cellY).first != BlockType::EMPTY) {
            return false;
        }
    }
    return true;
}

// function to move a block to left
void BoardModel::left(int m, bool doesPostMove, bool doesNotify) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first - 1, 
                                     curBlock_->getCoords().second, 
                                     curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first - 1, curBlock_->getCoords().second);
        m--;
    }
    if (doesPostMove) levelArray_.at(curBlockLevel_)->postMoveOperation();
    if (doesNotify) notify();
}

// function to move a block to right
void BoardModel::right(int m, bool doesPostMove, bool doesNotify) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first + 1, 
                                     curBlock_->getCoords().second, 
                                     curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first + 1, curBlock_->getCoords().second);
        m--;
    }
    if (doesPostMove) levelArray_.at(curBlockLevel_)->postMoveOperation();
    if (doesNotify) notify();
}

// function to move down a block
void BoardModel::down(int m, bool doesPostMove, bool doesNotify) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                                     curBlock_->getCoords().second - 1, 
                                     curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first, curBlock_->getCoords().second - 1);
        m--;
    }
    if (doesPostMove) levelArray_.at(curBlockLevel_)->postMoveOperation();
    if (doesNotify) notify();
}

// function to move a block clockwise
void BoardModel::clockwise(int m, bool doesPostMove, bool doesNotify) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                                     curBlock_->getCoords().second, 
                                    (curBlock_->getRotation() + 1) % 4)) {
        curBlock_->setRotation((curBlock_->getRotation() + 1) % 4);
        m--;
    }
    if (doesPostMove) levelArray_.at(curBlockLevel_)->postMoveOperation();
    if (doesNotify) notify();
}

// function to move a block counterclockwise
void BoardModel::counterclockwise(int m, bool doesPostMove, bool doesNotify) {
    // Incrementing by 3 (mod 4) is equivalent to subtracting 1 (mod 4)
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                                     curBlock_->getCoords().second, 
                                    (curBlock_->getRotation() + 3) % 4)) {
        curBlock_->setRotation((curBlock_->getRotation() + 3) % 4);
        m--;
    }
    if (doesPostMove) levelArray_.at(curBlockLevel_)->postMoveOperation();
    if (doesNotify) notify();
}

// function to drop a block
void BoardModel::drop(int m = 1) {
    // Move block down as far as possible
    while (m > 0 && !isGameOver_) {
        down(gridY_, false, false);

        std::vector<std::pair<int, int>> cells = curBlock_->getCells().at(curBlock_->getRotation());
        int x = curBlock_->getCoords().first;
        int y = curBlock_->getCoords().second;
        // Iterate through the 4 squares of the block and insert them into the grid_
        for(std::size_t i = 0; i < cells.size(); ++i) {
            setCell(x+cells[i].first, y+cells[i].second, std::make_pair(curBlock_->getType(), timestamp_));
        }

        levelArray_[level_]->postDropOperation(); // perform post drop operations

        liveBlocks_.insert(std::make_pair(timestamp_, std::make_pair(4, curBlock_->getLevelGenerated())));
        timestamp_++; // increment the time stamp

        checkCompletedRows();
        curBlock_ = nextBlock_; // update the current block
        nextBlock_ = levelArray_[level_]->generateNextBlock(); // update the next block
        curBlockLevel_ = nextBlockLevel_;
        nextBlockLevel_ = level_;

        isGameOver_ = !checkIfValidMove(curBlock_->getCoords().first, curBlock_->getCoords().second, curBlock_->getRotation());
        m--;
    }
    notify();
}

// function to handle the levelup command
void BoardModel::levelup(int m = 1) {
    level_ = level_ + m >= (int)levelArray_.size() ? (int)levelArray_.size() - 1 : level_ + m;
    notify();
}

// function to handle the leveldown command
void BoardModel::leveldown(int m = 1) {
    level_ = level_ - m < 0 ? 0 : level_ - m;
    notify();
}

// function to check completed rows
void BoardModel::checkCompletedRows() {
  // check completed rows
    int y = 0;
    int x = 0;
    int rowsCleared = 0;

    // Iterate from bottom-left to top-right of grid_
    while (y < gridY_) {
        // First, check if a row is completely full
        bool isRowComplete = true;
        while (x < gridX_) {
            if (getCell(x, y).first == BlockType::EMPTY) {
                isRowComplete = false;
                break;
            }
            x++;
        }

        if (isRowComplete) {
            nonClearStreak_ = 0;
            // Iterate through row for a second time to process scores, clear cells, and shift down cells
            x = 0;
            while (x < gridX_) {
                // Look-up the current cell's data in liveBlocks_ using its timestamp
                auto it = liveBlocks_.find(getCell(x,y).second);
                if (it != liveBlocks_.end()) {
                    if (it->second.first <= 1) {
                        // All of block's cells have been cleared
                        // Add BONUS POINTS
                        score_ += pow((it->second.second + 1), 2);
                        liveBlocks_.erase(getCell(x,y).second);
                    } else {
                        // Block has only been partially cleared
                        it->second.first = it->second.first - 1;
                    }
                }
                // Walk upwards in y direction from current cell,
                // shifting cells above down by 1
                int i = y;
                while (i < gridY_ - 1) {
                    std::pair<BlockType, int> above = getCell(x, i+1);
                    setCell(x, i, above);
                    i++;
                }
                // There is nothing to shift down from above in the top row;
                // the cell in the topmost row will be EMPTY
                setCell(x, gridY_-1, std::make_pair(BlockType::EMPTY, 0));
                x++;
            }
            x = 0;
            rowsCleared++;
            // Note, we do not increment y because all rows above have shifted down by 1
        } else {
            nonClearStreak_++;
            x = 0;
            y++;
        }
    }

    if (rowsCleared > 0) {
        // Add REGULAR POINTS
        score_ += pow((level_ + rowsCleared), 2);
    }
    
    if (score_ > hi_score_) {
        hi_score_ = score_;
    }
}

// function to handle the I command, change current block to I
void BoardModel::I(int m) {
    std::shared_ptr<GenericBlock> newBlock = std::make_shared<IBlock>();
    newBlock->setLevelGenerated(level_);
    curBlock_ = newBlock;
    notify();
}

// function to handle the J command, change current block to J
void BoardModel::J(int m) {
    std::shared_ptr<GenericBlock> newBlock = std::make_shared<JBlock>();
    newBlock->setLevelGenerated(level_);
    curBlock_ = newBlock;
    notify();
}

// function to handle the L command, change current block to L
void BoardModel::L(int m) {
    std::shared_ptr<GenericBlock> newBlock = std::make_shared<LBlock>();
    newBlock->setLevelGenerated(level_);
    curBlock_ = newBlock;
    notify();
}

// function to handle the S command, change current block to S
void BoardModel::S(int m) {
    std::shared_ptr<GenericBlock> newBlock = std::make_shared<SBlock>();
    newBlock->setLevelGenerated(level_);
    curBlock_ = newBlock;
    notify();
}

// function to handle the Z command, change current block to Z
void BoardModel::Z(int m) {
    std::shared_ptr<GenericBlock> newBlock = std::make_shared<ZBlock>();
    newBlock->setLevelGenerated(level_);
    curBlock_ = newBlock;
    notify();
}

// function to handle the O command, change current block to O
void BoardModel::O(int m) {
    std::shared_ptr<GenericBlock> newBlock = std::make_shared<OBlock>();
    newBlock->setLevelGenerated(level_);
    curBlock_ = newBlock;
    notify();
}

// function to handle the T command, change current block to T
void BoardModel::T(int m) {
    std::shared_ptr<GenericBlock> newBlock = std::make_shared<TBlock>();
    newBlock->setLevelGenerated(level_);
    curBlock_ = newBlock;
    notify();
}

// function to handle the restart command, restart the game
void BoardModel::restart() {
    // Reset grid
    isGameOver_ = false;
    std::vector<std::vector<std::pair<BlockType, int>>> grid(gridY_, std::vector <std::pair<BlockType, int>> (gridX_, std::make_pair(BlockType::EMPTY, 0)));
    grid_ = grid;
    score_ = 0;
    level_ = 0;
    levelArray_.at(level_)->setCounter(0); //reset the counter
    // generate new blocks
    curBlock_ = levelArray_.at(level_)->generateNextBlock();
    nextBlock_ = levelArray_.at(level_)->generateNextBlock();
    curBlockLevel_ = level_;
    nextBlockLevel_ = level_;
    notify();
}

// function to set game to random mode
void BoardModel::random() {
    levelArray_.at(level_)->setIsNonRandom(false);
}

// function to handle the hint command, gives a hint to the user
void BoardModel::hint() {
    // Tries out all x positions and rotations using the curBlock_ and sets the hintBlock_
    // to the configuration that gives the lowest y position after a drop

    // Create a temp copy of curBlock to restore it after computing the hint
    std::shared_ptr<GenericBlock> temp = std::make_shared<GenericBlock>(*curBlock_); // * allowed here since not expressing ownership.
    // Tracks values for the position that gives the lowest y value so far
    int bestY = 18;
    int bestRotation = 0;
    int bestX = 0;

    // Move curBlock_ to its initial spawn position and rotation
    curBlock_->setRotation(0);
    int m = gridY_;
    // Move up as high as possible
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                                curBlock_->getCoords().second + 1, 
                                curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first, curBlock_->getCoords().second + 1);
        m--;
    }
    // Move left as far as possible
    left(gridX_, false, false);
    // Bring it down to spawn height
    down(4, false, false);
    std::pair<int, int> baseCoords = curBlock_->getCoords();

    // Iterate through all rotations and x values
    for (int r = 0; r < 4; r++) {
        for (int x = 0; x < gridX_; x++) {
            // Reset position
            curBlock_->setCoords(baseCoords.first, baseCoords.second);
            // Transform and drop
            clockwise(r, false, false);
            right(x, false, false);
            down(gridY_, false, false);
            // Check if this is the lowest position so far
            if (curBlock_->getCoords().second < bestY) {
                bestY = curBlock_->getCoords().second;
                bestRotation = r;
                bestX = x;
            }
        }
    }

    // Reset to base position and rotation
    curBlock_->setRotation(0);
    curBlock_->setCoords(baseCoords.first, baseCoords.second);

    // Move to the best position and copy to hintBlock_
    clockwise(bestRotation, false, false);
    right(bestX, false, false);
    down(18, false, false);
    hintBlock_ = std::make_shared<GenericBlock>(*curBlock_); // * allowed here since not expressing ownership.

    // Restore curBlock_
    curBlock_ = temp;
    notify();
}

// function to handle the save game command, a bonus feature
// save game state to txt
void BoardModel::saveGame(std::string file) {
    std::cout << "SAVING TO " << file << "..." << std::endl;
    std::ofstream saveFile;
    saveFile.open (file);
    // Write each major member of BoardModel to a line in the save file
    saveFile << timestamp_ << "\n";
    saveFile << nonClearStreak_ << "\n";
    saveFile << score_ << "\n";
    saveFile << hi_score_ << "\n";
    saveFile << level_ << "\n";
    // Iterate through grid_ and print each element in a cell pair on its own line
    for (int i = 0; i < gridY_; i++) {
        for (int j = 0; j < gridX_; j++) {
            saveFile << (int)grid_.at(i).at(j).first << "\n";
            saveFile << grid_.at(i).at(j).second << "\n";
        }
    }
    saveFile << "\n";
    saveFile.close();
    std::cout << "SAVE COMPLETE!" << std::endl; // output the save complete message
}

// function to handle the load game command, a bonus feature
// load game state from txt
void BoardModel::loadGame(std::string file) {
    std::cout << "LOADING " << file << "..." << std::endl;
    restart();
    std::ifstream infile(file);
    std::string line;

    // Will be set to true if a line read ever fails
    bool didLoadFail = false;

    if (!std::getline(infile, line)) {
        didLoadFail = true;
    } else {
        setTimestamp(std::stoi(line));
    }
    
    if (!std::getline(infile, line)) {
        didLoadFail = true;
    } else {
        setNonClearStreak(std::stoi(line));
    }

    if (!std::getline(infile, line)) {
        didLoadFail = true;
    } else {
        setScore(std::stoi(line));
    }

    if (!std::getline(infile, line)) {
        didLoadFail = true;
    } else {
        setHiScore(std::stoi(line));
    }

    if (!std::getline(infile, line)) {
        didLoadFail = true;
    } else {
        setLevel(std::stoi(line));
    }

    // Iterate through grid_ to set each cell
    for (int i = 0; i < gridY_; i++) {
        for (int j = 0; j < gridX_; j++) {
            std::string type, id;
            if (!std::getline(infile, type) || !std::getline(infile, id)) {
                didLoadFail = true;
                break;
            } else {
                grid_.at(i).at(j) = std::make_pair((BlockType)std::stoi(type), std::stoi(id));
            }
        }
        if (didLoadFail) {
            break;
        }
    }

    if (didLoadFail) {
        std::cout << "WARNING: Some data could not be successfully loaded." << std::endl;;
    }

    std::cout << "LOAD COMPLETE!" << std::endl; // output the load complete message
    notify();
}
