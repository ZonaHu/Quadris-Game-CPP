//
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "BoardModel.h"

BoardModel::BoardModel() {
    std::vector<std::vector <char>> grid(gridY_, std::vector <char> (gridX_, ' '));
    grid_ = grid;
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
    while (checkIfValidMove(curBlock_->getCoords().first + 1, 
                            curBlock_->getCoords().second, 
                            curBlock_->getRotation())) {
        curBlock_->setCoords(curBlock_->getCoords().first + 1, curBlock_->getCoords().second);
        m--;
    }
}