#include "GenericLevel.h"

class Level4: public GenericLevel{
private:
  int seed_;
  int counter_;
public:
  Level4(const std::weak_ptr<BoardModel> p, int seed, bool nonrandom); // constructor
  ~Level4(){};  // default destructor
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};
