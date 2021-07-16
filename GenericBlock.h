// GenericBlock.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_GENERICBLOCK_H
#define PROJECT_2_3_GENERICBLOCK_H
#include <iostream>
#include <vector>

// Represents the block that the user is currently controlling
enum BlockType{
  I, // denotes Blocks with Type I
  J, // denotes Blocks with Type J
  L, // denotes Blocks with Type L
  O, // denotes Blocks with Type O
  S, // denotes Blocks with Type S
  Z, // denotes Blocks with Type Z
  T,  // denotes Blocks with Type T
  Star // denotes the star block in level 4
};

class GenericBlock {
protected:
  BlockType type_; // Takes on an enum type representing the block type

  std::vector <std::tuple<std::pair<int, int> , std::pair<int, int>, std::pair<int, int> ,std::pair<int, int>>>
      cells; // A 4-long vector of 4-tuples each containing the relative coordinates
             // (relative to bottom left) of the cells of the block for each rotation

  int rotation_; // Represents the index in cells for each rotation.
                 // For example, index 0 is 0 degrees, index 1 is 90 degrees, etc.


  // x and y are coordinates for the bottom left corner of the block
  int x_;
  int y_;

public:
  GenericBlock(); // default constructor
  ~GenericBlock(); // destructor

  // getter for a block's type
  BlockType getType() const;
  // setter for a block's type
  void setType();

  // getter for current cells
  std::vector <std::tuple<std::pair<int, int> , std::pair<int, int>, std::pair<int, int> ,std::pair<int, int>>>
    getCells();
  // setter for current cells
  void setCells();

  // getter for current rotation
  int getRotation() const;
  // setter for current rotation
  void setRotation();

  // getter for current coordinates
  std::pair <int, int> getCoords() const;
  // setter for current coordinates
  void setCoords();
};

class IBlock: public GenericBlock{
public:
  // default constructor, initialize the members with the appropriate values (i.e. type, cells, x, y)
  IBlock();
  // destructor to clean up memory
  ~IBlock();
};

class JBlock: public GenericBlock{
public:
  // default constructor, initialize the members with the appropriate values (i.e. type, cells, x, y)
  JBlock();
  // destructor to clean up memory
  ~JBlock();
};

class LBlock: public GenericBlock{
public:
  // default constructor, initialize the members with the appropriate values (i.e. type, cells, x, y)
  LBlock();
  // destructor to clean up memory
  ~LBlock();
};

class SBlock: public GenericBlock{
public:
  // default constructor, initialize the members with the appropriate values (i.e. type, cells, x, y)
  SBlock();
  // destructor to clean up memory
  ~SBlock();
};

class ZBlock: public GenericBlock{
public:
  // default constructor, initialize the members with the appropriate values (i.e. type, cells, x, y)
  ZBlock();
  // destructor to clean up memory
  ~ZBlock();
};

class OBlock: public GenericBlock{
public:
  // default constructor, initialize the members with the appropriate values (i.e. type, cells, x, y)
  OBlock();
  // destructor to clean up memory
  ~OBlock();
};

class TBlock: public GenericBlock{
public:
  // default constructor, initialize the members with the appropriate values (i.e. type, cells, x, y)
  TBlock();
  ~TBlock(); // destructor to clean up memory
};

class StarBlock: public GenericBlock{
  // the special block in level 4 (indicated by * in text, and by the colour brown in graphics)
public:
  // default constructor, initialize the members with the appropriate values (i.e. type, cells, x, y)
  StarBlock();
  ~StarBlock(); // destructor to clean up memory
};

#endif // PROJECT_2_3_GENERICBLOCK_H