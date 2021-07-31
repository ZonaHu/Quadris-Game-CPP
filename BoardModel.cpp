//
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "BoardModel.h"
#include <utility>
#include <math.h> 

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

int BoardModel::getHiScore() const { return hi_score_; }

int BoardModel::getLevel() const { return level_; }

int BoardModel::getNonClearStreak() const { return nonClearStreak_; }

void BoardModel::setNonClearStreak(int n) { nonClearStreak_ = n; }

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
    // Add REGULAR POINTS
    score_ += pow((level_ + rowsCleared), 2);
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
    // Reset grid
    std::vector<std::vector<std::pair<BlockType, int>>> grid(gridY_, std::vector <std::pair<BlockType, int>> (gridX_, std::make_pair(BlockType::EMPTY, 0)));
    grid_ = grid;
    score_ = 0;
    level_ = 0;
    curBlock_ = levelArray_.at(level_)->generateNextBlock();
    nextBlock_ = levelArray_.at(level_)->generateNextBlock();
}

void BoardModel::random() {
    levelArray_.at(level_)->setIsNonRandom(true);
}

void BoardModel::hint() {
    // Create a temp copy of curBlock to restore it after computing the hint
    std::shared_ptr<GenericBlock> temp = std::make_shared<GenericBlock>(*curBlock_);
    // Tracks values for the position that gives the lowest y value so far
    int bestY = 18;
    int bestRotation = 0;
    int bestX = 0;

    // Move curBlock_ to the top-left corner and set it as the base position
    int m = 18;
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                                curBlock_->getCoords().second + 1, 
                                curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first, curBlock_->getCoords().second + 1);
        m--;
    }
    left(11, false, false);
    std::pair<int, int> baseCoords = curBlock_->getCoords();

    // Iterate through all rotations and x values
    for (int r = 0; r < 4; r++) {
        for (int x = 0; x < 11; x++) {
            // Reset position
            curBlock_->setCoords(baseCoords.first, baseCoords.second);
            // Transform and drop
            clockwise(r, false, false);
            right(x, false, false);
            down(18, false, false);

            // Check if this is the lowest position so far
            if (curBlock_->getCoords().second < bestY) {
                bestY = curBlock_->getCoords().second;
                bestRotation = r;
                bestX = x;
            }
        }
    }

    // Move to the best position and copy to hintBlock_
    clockwise(bestRotation, false, false);
    right(bestX, false, false);
    down(18, false, false);
    hintBlock_ = std::make_shared<GenericBlock>(*curBlock_);

    // Restore curBlock_
    curBlock_ = temp;
    notify();
}