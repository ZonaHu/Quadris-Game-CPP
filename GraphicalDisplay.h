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
  BoardModel* boardModel_;

public:
  GraphicalDisplay();
  ~GraphicalDisplay();
  void update () override; //function for updating in observer

};

#endif // PROJECT_2_3_GRAPHICALDISPLAY_H
