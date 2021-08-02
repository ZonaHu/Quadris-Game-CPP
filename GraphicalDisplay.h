// GraphicalDisplay.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_GRAPHICALDISPLAY_H
#define PROJECT_2_3_GRAPHICALDISPLAY_H
#include "Observer.h"
#include "BoardModel.h"
#include <gtkmm-3.0/gtkmm/window.h>

class BoardModel;

class GraphicalDisplay: public Observer {
private:
  std::weak_ptr<BoardModel> boardModel_;

public:
  Gtk::Window* window_;
  explicit GraphicalDisplay(std::shared_ptr<BoardModel>, Gtk::Window *win);
  ~GraphicalDisplay() override;
  void update () override; //function for updating in observer
  void windowInit();
  std::shared_ptr<BoardModel> getBoardModel() const;
};

#endif // PROJECT_2_3_GRAPHICALDISPLAY_H
