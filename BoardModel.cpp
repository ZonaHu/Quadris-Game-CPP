//
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "BoardModel.h"
#include <utility>
#include <math.h> 

BoardModel::BoardModel() {
    std::vector<std::vector<std::pair<BlockType, int>>> grid(gridY_, std::vector <std::pair<BlockType, int>> (gridX_, std::make_pair(EMPTY, 0)));
    grid_ = grid;
}

BoardModel::BoardModel(int seed = 0, std::string scriptFile = "", int startLevel = 0) {
    std::vector<std::vector<std::pair<BlockType, int>>> grid(gridY_, std::vector <std::pair<BlockType, int>> (gridX_, std::make_pair(EMPTY, 0)));
    // TODO: Instantiate level objects in levelArray_

    grid_ = grid;
    score_ = 0;
    hi_score_ = 0;
    level_ = startLevel;
    curBlock_ = levelArray_.at(level_)->generateNextBlock();
    nextBlock_ = levelArray_.at(level_)->generateNextBlock();
}

BoardModel::~BoardModel() {}

std::vector <std::vector <std::pair<BlockType, int>>> BoardModel::getGrid() {
    return grid_;
}

// Transform Cartesian coords to indices in grid_ vector
// i.e. (0,0) is bottom left corner of grid
std::pair<BlockType, int> BoardModel::getCell(int x, int y) const {
    return grid_.at(gridY_-1-y).at(x);
}

std::shared_ptr<GenericBlock> BoardModel::getCurBlock() { return curBlock_; }

std::shared_ptr<GenericBlock> BoardModel::getNextBlock() { return nextBlock_; }

int BoardModel::getScore() { return score_; }

int BoardModel::getHiScore() { return hi_score_; }

int BoardModel::getLevel() { return level_; }

int BoardModel::getNonClearStreak() { return nonClearStreak_; }

void BoardModel::setNonClearStreak(int n) {
    nonClearStreak_ = n;
}

void BoardModel::setCell(int x, int y, std::pair<BlockType, int> data) {
    grid_.at(gridY_-1-y).at(x) = data;
}

bool BoardModel::checkIfValidMove(int x, int y, int r) {
    // Get cells of curBlock_ that correspond to rotation r
    std::vector<std::pair<int, int>> cells = curBlock_->getCells().at(r);

    for(std::size_t i = 0; i < cells.size(); ++i) {
        int cellX = x+cells[i].first;
        int cellY = y+cells[i].second;
        // Out of bounds check
        if (cellX < 0 || cellX > gridX_ - 1 || cellY < 0 || cellY > gridY_ - 1) {
            return false;
        } 
        // Non-empty cell check
        if (getCell(cellX, cellY).first != EMPTY) {
            return false;
        }
    }
    return true;
}

void BoardModel::left(int m = 1) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first + 1, 
                            curBlock_->getCoords().second, 
                            curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first + 1, curBlock_->getCoords().second);
        m--;
    }
    levelArray_.at(level_)->postMoveOperation();
    notify();
}

void BoardModel::right(int m = 1) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first - 1, 
                            curBlock_->getCoords().second, 
                            curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first - 1, curBlock_->getCoords().second);
        m--;
    }
    levelArray_.at(level_)->postMoveOperation();
    notify();
}

void BoardModel::down(int m = 1) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                            curBlock_->getCoords().second - 1, 
                            curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first, curBlock_->getCoords().second - 1);
        m--;
    }
    levelArray_.at(level_)->postMoveOperation();
    notify();
}

void BoardModel::clockwise(int m = 1) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                            curBlock_->getCoords().second - 1, 
                            (curBlock_->getRotation() + 1) % 4)) {
        curBlock_->setRotation((curBlock_->getRotation() + 1) % 4);
        m--;
    }
    levelArray_.at(level_)->postMoveOperation();
    notify();
}

void BoardModel::counterclockwise(int m = 1) {
    // Incrementing by 3 (mod 4) is equivalent to subtracting 1 (mod 4)
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                            curBlock_->getCoords().second - 1, 
                            (curBlock_->getRotation() + 3) % 4)) {
        curBlock_->setRotation((curBlock_->getRotation() + 3) % 4);
        m--;
    }
    levelArray_.at(level_)->postMoveOperation();
    notify();
}

void BoardModel::drop(int m = 1) {
    std::vector<std::pair<int, int>> cells = curBlock_->getCells().at(curBlock_->getRotation());
    int x = curBlock_->getCoords().first;
    int y = curBlock_->getCoords().second;
    for(std::size_t i = 0; i < cells.size(); ++i) {
        setCell(x+cells[i].first, y+cells[i].second, std::make_pair(curBlock_->getType(), timestamp_));
    }
    levelArray_[level_]->postDropOperation();
    checkCompletedRows();
    curBlock_ = nextBlock_;
    nextBlock_ = levelArray_[level_]->generateNextBlock();
    // TODO: Disable moves and only allow RESTART
    isGameOver_ = !checkIfValidMove(curBlock_->getCoords().first, curBlock_->getCoords().second, curBlock_->getRotation());
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
    int score = 0;
    int y = 0;
    int x = 0;
    int rowsCleared = 0;

    // Iterate from bottom left to top right of grid_
    while (y < gridY_) {
        // First, check if a row is completely full
        bool isRowComplete = true;
        while (x < gridX_) {
            if (getCell(x, y).first == EMPTY) {
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
                        score += pow((it->second.second + 1), 2);
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
                // Cell in topmost row will be EMPTY
                setCell(x, gridY_-1, std::make_pair(EMPTY, 0));
                x++;
            }
            rowsCleared++;
            // Note, we do not increment y because all rows above have shifted down by 1
        } else {
            nonClearStreak_++;
            x = 0;
            y++;
        }
        // Add REGULAR POINTS
        score += pow((level_ + rowsCleared), 2);
    }
}

void BoardModel::I() {
    std::shared_ptr<GenericBlock> newBlock(new IBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::J() {
    std::shared_ptr<GenericBlock> newBlock(new JBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::L() {
    std::shared_ptr<GenericBlock> newBlock(new LBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::S() {
    std::shared_ptr<GenericBlock> newBlock(new SBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::Z() {
    std::shared_ptr<GenericBlock> newBlock(new ZBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::O() {
    std::shared_ptr<GenericBlock> newBlock(new OBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::T() {
    std::shared_ptr<GenericBlock> newBlock(new TBlock());
    curBlock_ = newBlock;
    notify();
}

void BoardModel::restart() {
    std::vector<std::vector<std::pair<BlockType, int>>> grid(gridY_, std::vector <std::pair<BlockType, int>> (gridX_, std::make_pair(EMPTY, 0)));
    grid_ = grid;
    score_ = 0;
    level_ = startLevel;
    curBlock_ = levelArray_.at(level_)->generateNextBlock();
    nextBlock_ = levelArray_.at(level_)->generateNextBlock();
}