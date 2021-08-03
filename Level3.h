// Level3.h
// Derived from GenericLevel
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.
#include "GenericLevel.h"

class Level3: public GenericLevel{
private:
  int seed_;
  int counter_;
public:
  Level3(const std::weak_ptr<BoardModel> p, int seed, bool nonrandom); // constructor
  ~Level3(){};  // default destructor
  // Determines next block based on probability or sequence file, depending on the level
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;   // Gets called after every move in BoardModel
  void postDropOperation() override;   // Gets called after every drop in BoardModel
  void setCounter(int) override; // function to reset the counter
};
