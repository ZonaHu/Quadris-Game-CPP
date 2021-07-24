//
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "BoardModel.h"

BoardModel::BoardModel() {
    std::vector<std::vector <BlockType>> grid(gridY_, std::vector <BlockType> (gridX_, EMPTY));
    grid_ = grid;
}

BoardModel::BoardModel(int seed = 0, std::string scriptFile = "", int startLevel = 0) {
    std::vector<std::vector <BlockType>> grid(gridY_, std::vector <BlockType> (gridX_, EMPTY));
    // TODO: Instantiate level objects in levelArray_

    grid_ = grid;
    level_ = startLevel;
    curBlock_ = levelArray_.at(level_)->generateNextBlock();
    nextBlock_ = levelArray_.at(level_)->generateNextBlock();
}

BoardModel::~BoardModel() {}

// Transform Cartesian coords to indices in grid_ vector
// i.e. (0,0) is bottom left corner of grid
char BoardModel::getCell(int x, int y) const {
    return grid_.at(gridY_-1-y).at(x);
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
        if (getCell(cellX, cellY) != ' ') {
            return false;
        }
    }
    return true;
}

void BoardModel::left(int m) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first + 1, 
                            curBlock_->getCoords().second, 
                            curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first + 1, curBlock_->getCoords().second);
        m--;
    }
    levelArray_.at(level_)->postMoveOperation();
}

void BoardModel::right(int m) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first - 1, 
                            curBlock_->getCoords().second, 
                            curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first - 1, curBlock_->getCoords().second);
        m--;
    }
    levelArray_.at(level_)->postMoveOperation();
}

void BoardModel::down(int m) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                            curBlock_->getCoords().second - 1, 
                            curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first, curBlock_->getCoords().second - 1);
        m--;
    }
    levelArray_.at(level_)->postMoveOperation();
}

void BoardModel::clockwise(int m) {
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                            curBlock_->getCoords().second - 1, 
                            (curBlock_->getRotation() + 1) % 4)) {
        curBlock_->setRotation((curBlock_->getRotation() + 1) % 4);
        m--;
    }
    levelArray_.at(level_)->postMoveOperation();
}

void BoardModel::counterclockwise(int m) {
    // Incrementing by 3 (mod 4) is equivalent to subtracting 1 (mod 4)
    while (m > 0 && checkIfValidMove(curBlock_->getCoords().first, 
                            curBlock_->getCoords().second - 1, 
                            (curBlock_->getRotation() + 3) % 4)) {
        curBlock_->setRotation((curBlock_->getRotation() + 3) % 4);
        m--;
    }
    levelArray_.at(level_)->postMoveOperation();
}

void BoardModel::drop(int m) {

}