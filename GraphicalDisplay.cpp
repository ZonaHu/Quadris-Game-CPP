// GraphicalDisplay.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.


#include "GraphicalDisplay.h"
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/label.h>

GraphicalDisplay::GraphicalDisplay(std::shared_ptr<BoardModel> boardModel, Gtk::Window* winptr):boardModel_{boardModel}{
	window_ = winptr;
	windowInit();
	update();
}
GraphicalDisplay::~GraphicalDisplay() {
	getBoardModel()->unsubscribe(this);
}

std::shared_ptr<BoardModel> GraphicalDisplay::getBoardModel() const {
  return boardModel_.lock();
}

void GraphicalDisplay::windowInit() {
	// Creating all widgets for the windows
	window_->set_default_size(500, 500);
	window_->set_title("Quadris");
	window_->set_icon_from_file("quadris.png"); // From https://thenounproject.com/term/tetris/28580/
	Gtk::Box containerBox(Gtk::ORIENTATION_HORIZONTAL); // Contains everything in the window (horizontal orientation)
	Gtk::Box rightSubBox(Gtk::ORIENTATION_VERTICAL); // vertical orientation, contains information to be displayed (score, next block, etc.)
	Gtk::Box leftSubBox(Gtk::ORIENTATION_VERTICAL); // vertical orientation, contains buttons for placing blocks, etc.
	// Creating title for window
	Gtk::Label titleLabel;
	titleLabel.set_text("Quadris");


}

void GraphicalDisplay::update() {}
