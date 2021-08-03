// Level4.h
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

class Level4: public GenericLevel{
private:
  int seed_; // seed
  int counter_; // current index for the block seq vector
public:
  Level4(const std::weak_ptr<BoardModel> p, int seed, bool nonrandom); // constructor
  ~Level4(){};  // default destructor
  // Determines next block based on probability or sequence file, depending on the level
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;   // Gets called after every move in BoardModel
  void postDropOperation() override;   // Gets called after every drop in BoardModel
  void setCounter(int) override; // function to reset the counter
};
