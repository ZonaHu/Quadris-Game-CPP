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
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/colorbutton.h>
#include <gtkmm-3.0/gtkmm/grid.h>
#include <vector>
#include <glib.h>
#include <utility>
#include <unordered_map>

class BoardModel;

class GraphicalDisplay: public Observer {
private:
  std::weak_ptr<BoardModel> boardModel_;
  std::unordered_map<BlockType, Gdk::RGBA> blockTypeToColour_;

public:
  // window components:
  Gtk::Window* window_;
  Gtk::Box containerBox; // contains everything in the window (horizontal orientation)
  Gtk::Box rightSubBox; // vertical orientation, contains information to be displayed (score, next block, etc.)
  Gtk::Box leftSubBox; // vertical orientation, contains buttons for placing blocks, etc.
  Gtk::Box leftButtonPanelBox; // horizontal orientation, contains two sub boxes
  Gtk::Box placingBlocksPanel; // left panel of the above box
  Gtk::Box otherButtonsPanel; // right panel, respectively
  Gtk::Box boardGridBox;
  Gtk::Box upcomingBlockGridBox;

  // label components
  Gtk::Label titleLabel; // title for the overall game
  Gtk::Label placingBlocksLabel; // title for the placing blocks subpanel
  Gtk::Label otherButtonsLabel; // title for the other buttons subpanel
  Gtk::Label upcomingBlockLabel; // title for the next block section
  Gtk::Label statsTitleLabel; // title for the stats section
  Gtk::Label levelLabel; // this line will show the current level
  Gtk::Label scoreLabel; // this line will show the current score
  Gtk::Label hiScoreLabel; // this score will show the current hi-score

  // button components (self-explanatory):
  Gtk::Button leftButton;
  Gtk::Button rightButton;
  Gtk::Button downButton;
  Gtk::Button CWButton;
  Gtk::Button CCWButton;
  Gtk::Button LevelUpButton;
  Gtk::Button LevelDownButton;
  Gtk::Button noRandomButton;
  Gtk::Button randomButton;
  Gtk::Button sequenceButton;
  Gtk::Button restartButton;
  Gtk::Button hintButton;
  Gtk::Button saveButton;
  Gtk::Button loadButton;

  // vector for button components (for easy of assigning functions):
  std::vector<Gtk::Button*> interfaceButtons;

  // grid components (container):
  Gtk::Grid boardGrid;
  Gtk::Grid upcomingBlockGrid;

  // cells of the grids:
  std::vector<std::vector<Gtk::ColorButton*>> buttonBoardGrid;
  std::vector<std::vector<Gtk::ColorButton*>> buttonUpcomingBlockGrid;

  // functions for initializing, destructing, and drawing on the window:
  explicit GraphicalDisplay(std::shared_ptr<BoardModel>, Gtk::Window *win);
  ~GraphicalDisplay() override;
  void update () override; // function for updating in observer
  void windowInit(); // for drawing the initial state of the window
  void onButtonClicked(const Glib::ustring&); // callback for the buttons on the window
  void dialogGeneration(); // for obtaining file paths through the GUI
  void getStatistics(); // for updating statistics (and getting them from the board model)
  void getNextBlock(); // for updating what the upcoming block is (getting it from board model)
  std::shared_ptr<BoardModel> getBoardModel() const;
};

#endif // PROJECT_2_3_GRAPHICALDISPLAY_H
