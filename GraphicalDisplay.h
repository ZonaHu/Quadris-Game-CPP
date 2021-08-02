// GraphicalDisplay.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_GRAPHICALDISPLAY_H
#define PROJECT_2_3_GRAPHICALDISPLAY_H
#include "Observer.h"
#include "BoardModel.h"
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/label.h>

class BoardModel;

class GraphicalDisplay: public Observer {
private:
  std::weak_ptr<BoardModel> boardModel_;

public:
  // window components:
  Gtk::Window* window_;
  Gtk::Box containerBox; // Contains everything in the window (horizontal orientation)
  Gtk::Box rightSubBox; // vertical orientation, contains information to be displayed (score, next block, etc.)
  Gtk::Box leftSubBox; // vertical orientation, contains buttons for placing blocks, etc.
  // Creating title for window
  Gtk::Label titleLabel;

  // functions for initializing, destructing, and drawing on the window:
  explicit GraphicalDisplay(std::shared_ptr<BoardModel>, Gtk::Window *win);
  ~GraphicalDisplay() override;
  void update () override; //function for updating in observer
  void windowInit();
  std::shared_ptr<BoardModel> getBoardModel() const;
};

#endif // PROJECT_2_3_GRAPHICALDISPLAY_H
