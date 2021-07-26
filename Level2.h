#include "GenericLevel.h"

class Level2: public GenericLevel{
private:
  int seed_;
public:
  Level2(const std::shared_ptr<BoardModel> p, int seed); // constructor
  ~Level2(){};  // default destructor
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};