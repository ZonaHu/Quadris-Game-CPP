//
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "BoardModel.h"
#include <utility>
#include <math.h>
#include <fstream>
#include <stdlib.h>

BoardModel::BoardModel() {
    std::vector<std::vector<std::pair<BlockType, int>>> grid(gridY_, std::vector <std::pair<BlockType, int>> (gridX_, std::make_pair(BlockType::EMPTY, 0)));
    grid_ = grid;
}

BoardModel::BoardModel(int seed, std::string scriptFile, int startLevel, bool enableBonus) {
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
    levelArray_ = levelArray;
    curBlock_ = levelArray_.at(level_)->generateNextBlock();
    nextBlock_ = levelArray_.at(level_)->generateNextBlock();
}

// Sets the block sequence for the current level
void BoardModel::setBlockGenSequence(std::vector<BlockType> seq) {
    levelArray_.at(level_)->setBlockGenSequence(seq);
    levelArray_.at(level_)->setIsNonRandom(true);
    curBlock_ = levelArray_.at(level_)->generateNextBlock();
    nextBlock_ = levelArray_.at(level_)->generateNextBlock();
}

int BoardModel::getGridX() const { return gridX_; }

int BoardModel::getGridY() const { return gridY_; }

std::vector <std::vector <std::pair<BlockType, int>>> BoardModel::getGrid() const { return grid_; }

// Transforms Cartesian coords to indices in grid_ vector
// i.e. (0,0) is bottom left corner of grid
std::pair<BlockType, int> BoardModel::getCell(int x, int y) const {
    return grid_.at(gridY_-1-y).at(x);
}

void BoardModel::setCell(int x, int y, std::pair<BlockType, int> data) {
    grid_.at(gridY_-1-y).at(x) = data;
}

std::shared_ptr<GenericBlock> BoardModel::getCurBlock() const { return curBlock_; }

std::shared_ptr<GenericBlock> BoardModel::getNextBlock() const { return nextBlock_; }

std::shared_ptr<GenericBlock> BoardModel::getHintBlock() const { return hintBlock_; }

void BoardModel::clearHintBlock() { hintBlock_ = nullptr; }

int BoardModel::getScore() const { return score_; }

void BoardModel::setScore(int score) { score_ = score; }

int BoardModel::getHiScore() const { return hi_score_; }

void BoardModel::setHiScore(int hi_score) { hi_score_ = hi_score; }

int BoardModel::getLevel() const { return level_; }

void BoardModel::setLevel(int level) { level_ = level; }

int BoardModel::getNonClearStreak() const { return nonClearStreak_; }

bool BoardModel::getIsGameOver() const { return isGameOver_; }

void BoardModel::setNonClearStreak(int n) { nonClearStreak_ = n; }

void BoardModel::setTimestamp(int t) { timestamp_ = t; }

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

void BoardModel::left(int m, bool doesPostMove, bool doesNotify) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first - 1, 
                                     curBlock_->getCoords().second, 
                                     curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first - 1, curBlock_->getCoords().second);
        m--;
    }
    if (doesPostMove) levelArray_.at(level_)->postMoveOperation();
    if (doesNotify) notify();
}

void BoardModel::right(int m, bool doesPostMove, bool doesNotify) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first + 1, 
                                     curBlock_->getCoords().second, 
                                     curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first + 1, curBlock_->getCoords().second);
        m--;
    }
    if (doesPostMove) levelArray_.at(level_)->postMoveOperation();
    if (doesNotify) notify();
}

void BoardModel::down(int m, bool doesPostMove, bool doesNotify) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                                     curBlock_->getCoords().second - 1, 
                                     curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first, curBlock_->getCoords().second - 1);
        m--;
    }
    if (doesPostMove) levelArray_.at(level_)->postMoveOperation();
    if (doesNotify) notify();
}

void BoardModel::clockwise(int m, bool doesPostMove, bool doesNotify) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                                     curBlock_->getCoords().second, 
                                    (curBlock_->getRotation() + 1) % 4)) {
        curBlock_->setRotation((curBlock_->getRotation() + 1) % 4);
        m--;
    }
    if (doesPostMove) levelArray_.at(level_)->postMoveOperation();
    if (doesNotify) notify();
}

void BoardModel::counterclockwise(int m, bool doesPostMove, bool doesNotify) {
    // Incrementing by 3 (mod 4) is equivalent to subtracting 1 (mod 4)
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                                     curBlock_->getCoords().second, 
                                    (curBlock_->getRotation() + 3) % 4)) {
        curBlock_->setRotation((curBlock_->getRotation() + 3) % 4);
        m--;
    }
    if (doesPostMove) levelArray_.at(level_)->postMoveOperation();
    if (doesNotify) notify();
}

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

        levelArray_[level_]->postDropOperation();

        liveBlocks_.insert(std::make_pair(timestamp_, std::make_pair(4, level_)));
        timestamp_++;

        checkCompletedRows();
        curBlock_ = nextBlock_;
        nextBlock_ = levelArray_[level_]->generateNextBlock();

        isGameOver_ = !checkIfValidMove(curBlock_->getCoords().first, curBlock_->getCoords().second, curBlock_->getRotation());
        m--;
    }
    notify();
}

void BoardModel::levelup(int m = 1) {
    level_ = level_ + m >= (int)levelArray_.size() ? (int)levelArray_.size() - 1 : level_ + m;
    notify();
}

void BoardModel::leveldown(int m = 1) {
    level_ = level_ - m < 0 ? 0 : level_ - m;
    notify();
}

void BoardModel::checkCompletedRows() {
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
            // Iterate through row for a second time to process scores, delete cells, and shift down cells
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

void BoardModel::I(int m) {
    std::shared_ptr<GenericBlock> newBlock(new IBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::J(int m) {
    std::shared_ptr<GenericBlock> newBlock(new JBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::L(int m) {
    std::shared_ptr<GenericBlock> newBlock(new LBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::S(int m) {
    std::shared_ptr<GenericBlock> newBlock(new SBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::Z(int m) {
    std::shared_ptr<GenericBlock> newBlock(new ZBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::O(int m) {
    std::shared_ptr<GenericBlock> newBlock(new OBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::T(int m) {
    std::shared_ptr<GenericBlock> newBlock(new TBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::restart() {
    // Reset grid
    isGameOver_ = false;
    std::vector<std::vector<std::pair<BlockType, int>>> grid(gridY_, std::vector <std::pair<BlockType, int>> (gridX_, std::make_pair(BlockType::EMPTY, 0)));
    grid_ = grid;
    score_ = 0;
    level_ = 0;
    curBlock_ = levelArray_.at(level_)->generateNextBlock();
    nextBlock_ = levelArray_.at(level_)->generateNextBlock();
    notify();
}

void BoardModel::random() {
    levelArray_.at(level_)->setIsNonRandom(false);
}

void BoardModel::hint() {
    // Tries out all x positions and rotations using the curBlock_ and sets the hintBlock_
    // to the configuration that gives the lowest y position after a drop

    // Create a temp copy of curBlock to restore it after computing the hint
    std::shared_ptr<GenericBlock> temp = std::make_shared<GenericBlock>(*curBlock_);
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
    hintBlock_ = std::make_shared<GenericBlock>(*curBlock_);

    // Restore curBlock_
    curBlock_ = temp;
    notify();
}

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
    std::cout << "SAVE COMPLETE!" << std::endl;
}

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
        std::cout << "WARNING: Some data could not be successfully loaded.";
    }

    std::cout << "LOAD COMPLETE!" << std::endl;
    notify();
}
