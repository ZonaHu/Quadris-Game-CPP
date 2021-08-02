// GraphicalDisplay.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.


#include "GraphicalDisplay.h"
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <glib.h>

GraphicalDisplay::GraphicalDisplay(std::shared_ptr<BoardModel> boardModel, Gtk::Window* winptr):boardModel_{boardModel}{
	window_ = winptr;
	windowInit();
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
	// Changing up the style of the title label
	titleLabel.override_color(Gdk::RGBA("green"), Gtk::STATE_FLAG_NORMAL);
	const char *str = "Quadris";
	const char *format = "<span style=\"italic\">\%s</span>";
	char *markup;
	markup = g_markup_printf_escaped(format, str);
	titleLabel.set_markup(markup);
	g_free(markup);

	// Setting sub-section orientations
	containerBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
	leftSubBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
	rightSubBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
	leftSubBox.add(titleLabel);
	containerBox.add(leftSubBox);
	containerBox.add(rightSubBox);
	window_->add(containerBox);
	window_->show_all_children();
}

void GraphicalDisplay::update() {}
