// GenericLevel.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.


#ifndef PROJECT_2_3_GENERICLEVEL_H
#define PROJECT_2_3_GENERICLEVEL_H
#include "BoardModel.h"
#include <memory>
#include "GenericBlock.h"
#include <random>

class BoardModel;

class GenericLevel {
protected:
  // a shared Pointer to BoardModel object
  std::shared_ptr <BoardModel> boardModel_;

public:
  GenericLevel(){}; // default constructor
  GenericLevel(const std::shared_ptr<BoardModel>& p); // constructor
  virtual ~GenericLevel(){}; // default destructor

  // Determines next block based on probability or sequence file, depending on the level
  virtual std::shared_ptr <GenericBlock> generateNextBlock() = 0;

  // Gets called after every move in BoardModel
  virtual void postMoveOperation() = 0;

  // Gets called after every drop() in BoardModel
  virtual void postDropOperation() = 0;
};

class Level0: public GenericLevel{
private:
  std::vector<char> blockSeq_;
  int counter_;
public:
  Level0(const std::shared_ptr<BoardModel> & p, std::vector<char> blockType); // constructor
  ~Level0(){};  // default destructor
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};

class Level1: public GenericLevel{
private:
  int seed_;
public:
  Level1(const std::shared_ptr<BoardModel> & p, int seed); // constructor
  ~Level1(){};  // default destructor
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};

class Level2: public GenericLevel{
private:
  int seed_;
public:
  Level2(const std::shared_ptr<BoardModel> & p, int seed); // constructor
  ~Level2(){};  // default destructor
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};

class Level3: public GenericLevel{
private:
  int seed_;
public:
  Level3(const std::shared_ptr<BoardModel> & p, int seed); // constructor
  ~Level3(){};  // default destructor
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};

class Level4: public GenericLevel{
private:
  int seed_;
public:
  Level4(const std::shared_ptr<BoardModel> & p, int seed); // constructor
  ~Level4(){};  // default destructor
  std::shared_ptr <GenericBlock> generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};

#endif // PROJECT_2_3_GENERICLEVEL_H
