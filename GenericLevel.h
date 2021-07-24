// GenericLevel.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.


#ifndef PROJECT_2_3_GENERICLEVEL_H
#define PROJECT_2_3_GENERICLEVEL_H
#include "BoardModel.h"
#include <memory>

class BoardModel;

class GenericLevel {
protected:
  // a shared Pointer to BoardModel object
  std::shared_ptr <BoardModel> boardModel_;

public:
  GenericLevel(const std::shared_ptr<BoardModel>&); // constructor
  virtual ~GenericLevel(){}; // destructor

  // Determines next block based on probability or sequence file, depending on the level
  virtual GenericBlock generateNextBlock() = 0;

  // Gets called after every move in BoardModel
  virtual void postMoveOperation() = 0;

  // Gets called after every drop() in BoardModel
  virtual void postDropOperation() = 0;
};

class Level0: public GenericLevel{
public:
  Level0(const std::shared_ptr<BoardModel> &unnamed);
  ~Level0();
  GenericBlock generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};

class Level1: public GenericLevel{
public:
  Level1();
  ~Level1();
  GenericBlock generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};

class Level2: public GenericLevel{
public:
  Level2();
  ~Level2();
  GenericBlock generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};

class Level3: public GenericLevel{
public:
  Level3();
  ~Level3();
  GenericBlock generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};

class Level4: public GenericLevel{
public:
  Level4();
  ~Level4();
  GenericBlock generateNextBlock() override;
  void postMoveOperation() override;
  void postDropOperation() override;
};

#endif // PROJECT_2_3_GENERICLEVEL_H
