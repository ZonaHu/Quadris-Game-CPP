// Level0.h
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "GenericLevel.h"

class Level0: public GenericLevel{
private:
  int counter_;
public:
  Level0(const std::weak_ptr<BoardModel> p, std::vector<BlockType> blockSeq); // constructor
  ~Level0(){};  // default destructor

  // Determines next block based on probability or sequence file, depending on the level
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;   // Gets called after every move in BoardModel
  void postDropOperation() override;   // Gets called after every drop in BoardModel
  void setCounter(int) override; // function to reset the counter
};