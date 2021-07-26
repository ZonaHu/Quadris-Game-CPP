#include "GenericLevel.h"

class Level1: public GenericLevel{
private:
  int seed_;
public:
  Level1(const std::shared_ptr<BoardModel> p, int seed); // constructor
  ~Level1(){};  // default destructor
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};