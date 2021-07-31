#include "GenericLevel.h"

class Level3: public GenericLevel{
private:
  int seed_;
  int counter_;
public:
  Level3(const std::shared_ptr<BoardModel> p, int seed, bool nonrandom); // constructor
  ~Level3(){};  // default destructor
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};
