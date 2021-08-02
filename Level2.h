#include "GenericLevel.h"

class Level2: public GenericLevel{
private:
  int seed_;
public:
  Level2(const std::weak_ptr<BoardModel> p, int seed); // constructor
  ~Level2(){};  // default destructor
  // Determines next block based on probability or sequence file, depending on the level
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;   // Gets called after every move in BoardModel
  void postDropOperation() override;   // Gets called after every drop in BoardModel
  void setCounter(int) override; // function to reset the counter
};