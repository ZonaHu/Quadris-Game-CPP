#include "GenericLevel.h"

class Level0: public GenericLevel{
private:
  int counter_;
public:
  Level0(const std::weak_ptr<BoardModel> p, std::vector<BlockType> blockSeq); // constructor
  ~Level0(){};  // default destructor
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};