// GraphicalDisplay.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_GRAPHICALDISPLAY_H
#define PROJECT_2_3_GRAPHICALDISPLAY_H
#include "Observer.h"


class BoardModel;

class GraphicalDisplay: public Observer{
  // TODO: To be implemented
private:
  std::weak_ptr<BoardModel> boardModel_;

public:
  GraphicalDisplay(std::shared_ptr<BoardModel>);
  ~GraphicalDisplay();
  void update () override; //function for updating in observer
  std::shared_ptr<BoardModel> getBoardModel() const;
};

#endif // PROJECT_2_3_GRAPHICALDISPLAY_H
