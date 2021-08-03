// GraphicalDisplay.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

//Finishing implementing save and load last

#include "GraphicalDisplay.h"
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/colorbutton.h>
#include <gtkmm-3.0/gtkmm/messagedialog.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm-3.0/gtkmm/grid.h>
#include <vector>
#include <string>
#include <glib.h>
#include <unordered_map>

GraphicalDisplay::GraphicalDisplay(std::shared_ptr<BoardModel> boardModel, Gtk::Window* winptr):boardModel_{boardModel}{
	window_ = winptr;
	blockTypeToColour_[BlockType::I_BLOCK] = "\U0001F7E6";// blue
	blockTypeToColour_[BlockType::J_BLOCK] = "\U0001F7E5"; // red
	blockTypeToColour_[BlockType::L_BLOCK] = "\U0001F7E9"; // green
	blockTypeToColour_[BlockType::O_BLOCK] = "\U0001F7E7"; // orange
	blockTypeToColour_[BlockType::S_BLOCK] = "\U0001F7EA"; // purple
	blockTypeToColour_[BlockType::Z_BLOCK] = "\U0001F7EB"; // brown
	blockTypeToColour_[BlockType::T_BLOCK] = "\U0001F7E8"; // yellow
	blockTypeToColour_[BlockType::STAR_BLOCK] = "\U00002B50"; // star
	blockTypeToColour_[BlockType::EMPTY] = " "; // grey
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
	// First, changing window title bar attributes
	window_->set_default_size(1000, 500);
	window_->set_title("Quadris");
	window_->set_icon_from_file("quadris.png"); // From https://thenounproject.com/term/tetris/28580/

	// Changing up the style of the title label inside the window
	titleLabel.override_color(Gdk::RGBA("green"), Gtk::STATE_FLAG_NORMAL);
	const char *str = "Quadris";
	const char *format = "<span style=\"italic\">\%s</span>";
	char *markup;
	markup = g_markup_printf_escaped(format, str);
	titleLabel.set_markup(markup);
	g_free(markup);

	// Setting sub-section orientations inside the window
	containerBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
	leftSubBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
	rightSubBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
	leftButtonPanelBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
	placingBlocksPanel.set_orientation(Gtk::ORIENTATION_VERTICAL);
	otherButtonsPanel.set_orientation(Gtk::ORIENTATION_VERTICAL);

	// Setting text for all of the other labels:
	placingBlocksLabel.set_text("Placing Block Options");
	otherButtonsLabel.set_text("Other Options");
	upcomingBlockLabel.set_text("Upcoming Block:");
	statsTitleLabel.set_text("Statistics:");
	levelLabel.set_text("Level: ");
	scoreLabel.set_text("Score: ");
	hiScoreLabel.set_text("Hi-Score: ");

	// Setting text for all of the buttons + connecting them to a callback:
	leftButton.set_label("Left");
	interfaceButtons.push_back(Gtk::manage(&leftButton));
	rightButton.set_label("Right");
	interfaceButtons.push_back(Gtk::manage(&rightButton));
	downButton.set_label("Down");
	interfaceButtons.push_back(Gtk::manage(&downButton));
	CWButton.set_label("Clockwise");
	interfaceButtons.push_back(Gtk::manage(&CWButton));
	CCWButton.set_label("Counter-clockwise");
	interfaceButtons.push_back(Gtk::manage(&CCWButton));
	LevelUpButton.set_label("Level Up");
	interfaceButtons.push_back(Gtk::manage(&LevelUpButton));
	LevelDownButton.set_label("Level Down");
	interfaceButtons.push_back(Gtk::manage(&LevelDownButton));
	noRandomButton.set_label("No Random");
	interfaceButtons.push_back(Gtk::manage(&noRandomButton));
	randomButton.set_label("Random");
	interfaceButtons.push_back(Gtk::manage(&randomButton));
	sequenceButton.set_label("Sequence");
	interfaceButtons.push_back(Gtk::manage(&sequenceButton));
	restartButton.set_label("Restart");
	interfaceButtons.push_back(Gtk::manage(&restartButton));
	hintButton.set_label("Hint");
	interfaceButtons.push_back(Gtk::manage(&hintButton));
	saveButton.set_label("Save");
	interfaceButtons.push_back(Gtk::manage(&saveButton));
	loadButton.set_label("Load");
	interfaceButtons.push_back(Gtk::manage(&loadButton));

	for (int i = 0 ; i < (int) interfaceButtons.size(); i++){
		interfaceButtons[i]->signal_clicked().connect(
		    sigc::bind<Glib::ustring>(sigc::mem_fun(*this,
		      &GraphicalDisplay::onButtonClicked), interfaceButtons[i]->get_label())
		);
	}

	// creating the grids for the board and for the upcoming block respectively (default colour is grey):
	// game board:
	for (int i = 0; i < 11; i++) {
		std::vector<Gtk::ColorButton*> row;
		for (int j = 0; j < 18; j++){
			Gtk::ColorButton* cell = new Gtk::ColorButton();
			cell->set_sensitive(false);
			cell->set_label(" ");
			row.push_back(Gtk::manage(cell));
		}
		buttonBoardGrid.push_back(row);
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 18; j++) {
			boardGrid.attach(*buttonBoardGrid[i][j], i, j, 1, 1);
		}
	}
	// for showing next block:
	for (int i = 0; i < 4; i++) {
		std::vector<Gtk::ColorButton*> row;
		for (int j = 0; j < 4; j++){
			Gtk::ColorButton* cell = new Gtk::ColorButton();
			cell->set_sensitive(false);
			cell->set_label(" ");
			row.push_back(Gtk::manage(cell));
		}
		buttonUpcomingBlockGrid.push_back(row);
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			upcomingBlockGrid.attach(*buttonUpcomingBlockGrid[i][j], i, j, 1, 1);
		}
	}
	// finally, organizing all the containing boxes and components and making a hierarchy:
	// left half of the window:
	placingBlocksPanel.add(placingBlocksLabel);
	placingBlocksPanel.add(leftButton);
	placingBlocksPanel.add(rightButton);
	placingBlocksPanel.add(downButton);
	placingBlocksPanel.add(CWButton);
	placingBlocksPanel.add(CCWButton);
	placingBlocksPanel.add(LevelUpButton);
	placingBlocksPanel.add(LevelDownButton);
	placingBlocksPanel.show_all();

	otherButtonsPanel.add(otherButtonsLabel);
	otherButtonsPanel.add(noRandomButton);
	otherButtonsPanel.add(randomButton);
	otherButtonsPanel.add(sequenceButton);
	otherButtonsPanel.add(restartButton);
	otherButtonsPanel.add(hintButton);
	otherButtonsPanel.show_all();

	leftButtonPanelBox.add(placingBlocksPanel);
	leftButtonPanelBox.add(otherButtonsPanel);
	leftButtonPanelBox.show_all();

	leftSubBox.add(titleLabel);
	boardGridBox.add(boardGrid);
	leftSubBox.add(boardGridBox);
	leftSubBox.add(leftButtonPanelBox);
	leftSubBox.show_all();

	// right half of the window:
	rightSubBox.add(upcomingBlockLabel);
	upcomingBlockGridBox.add(upcomingBlockGrid);
	rightSubBox.add(upcomingBlockGridBox);
	rightSubBox.add(statsTitleLabel);
	rightSubBox.add(levelLabel);
	rightSubBox.add(scoreLabel);
	rightSubBox.add(hiScoreLabel);

	containerBox.add(leftSubBox);
	containerBox.add(rightSubBox);
	window_->add(containerBox);
	window_->show_all_children();
}

void GraphicalDisplay::update() {
	getStatistics();
	getNextBlock();
	generateBoard();
	window_->show_all_children();
}

// The callback basically works by pushing the relevant command to the output stream.
void GraphicalDisplay::onButtonClicked(const Glib::ustring& data) {
	if (data == "Left") {
		std::cout << "left" << std::endl;
	} else if (data == "Right") {
		std::cout << "right" << std::endl;
	} else if (data == "Down") {
		std::cout << "down" << std::endl;
	} else if (data == "Clockwise") {
		std::cout << "clockwise" << std::endl;
	} else if (data == "Counter-clockwise") {
		std::cout << "counterclockwise" << std::endl;
	} else if (data == "Drop") {
		std::cout << "drop" << std::endl;
	} else if (data == "Level Up") {
		std::cout << "levelup" << std::endl;
	} else if (data == "Level Down") {
		std::cout << "leveldown" << std::endl;
	} else if (data == "No Random") {
		std::cout << "norandom ";
		dialogGeneration();
	} else if (data == "Random") {
		std::cout << "random" << std::endl;
	} else if (data == "Sequence") {
		std::cout << "sequence ";
		dialogGeneration();
	}else if (data == "Restart") {
		std::cout << "restart" << std::endl;
	} else if (data == "Hint") {
		std::cout << "hint" << std::endl;
	} else if (data == "Save") {
		std::cout << "save" << std::endl;
	} else if (data == "Load") {
		// potentially need another dialog here
		std::cout << "load" << std::endl;
	}
}

void GraphicalDisplay::dialogGeneration() {
	  Gtk::MessageDialog fileDialog(*window_, "Please type in the file path.", false,
			  Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL); // we need dialogs so that we can get a filename through the GUI (for sequence and norandom)
	  Gtk::Entry textField;
	  textField.set_visibility(true);
	  textField.set_size_request(250, 0);
	  textField.set_text("Insert file path here!");
	  fileDialog.get_vbox()->pack_start(textField, Gtk::PACK_SHRINK);
	  fileDialog.show_all();
	  int result = fileDialog.run();
	  std::string filePath = textField.get_text();
	  if (result == Gtk::RESPONSE_OK){
		  std::cout << filePath << std::endl;
	  }
}

void GraphicalDisplay::getStatistics() {
	Glib::ustring levelUpdate = Glib::ustring::format(getBoardModel()->getLevel());
	levelLabel.set_text("Level: " + levelUpdate);

	Glib::ustring scoreUpdate = Glib::ustring::format(getBoardModel()->getScore());
	scoreLabel.set_text("Score: " + scoreUpdate);

	Glib::ustring hiScoreUpdate = Glib::ustring::format(getBoardModel()->getHiScore());
	hiScoreLabel.set_text("Hi-Score: " + hiScoreUpdate);
}

void GraphicalDisplay::getNextBlock() {
	std::shared_ptr <GenericBlock> nextBlock = getBoardModel()->getNextBlock(); // get the next block we want
	// getting the coordinates of each aspect of the block:
	std::pair <int, int> a = nextBlock->getCells().at(0).at(0);
	std::pair <int, int> b = nextBlock->getCells().at(0).at(1);
	std::pair <int, int> c = nextBlock->getCells().at(0).at(2);
	std::pair <int, int> d = nextBlock->getCells().at(0).at(3);

	std::cout << a.first << " " << a.second << std::endl;
	std::cout << b.first << " " << b.second << std::endl;
	std::cout << c.first << " " << c.second << std::endl;
	std::cout << d.first << " " << d.second << std::endl;

	//resetting the grid to blank + colouring the four cells of the upcoming block
	for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (j == a.first && i == (3 - a.second)){
					buttonUpcomingBlockGrid.at(a.first).at(3 - a.second)->set_label(blockTypeToColour_.at(nextBlock->getType()));
				} else if (j == b.first && i == (3 - b.second)){
					buttonUpcomingBlockGrid.at(b.first).at(3 - b.second)->set_label(blockTypeToColour_.at(nextBlock->getType()));
				} else if (j == c.first && i == (3 - c.second)){
					buttonUpcomingBlockGrid.at(c.first).at(3 - c.second)->set_label(blockTypeToColour_.at(nextBlock->getType()));
				} else if (j == d.first && i == (3 - d.second)){
					buttonUpcomingBlockGrid.at(d.first).at(3 - d.second)->set_label(blockTypeToColour_.at(nextBlock->getType()));
				} else {
					buttonUpcomingBlockGrid.at(i).at(j)->set_label(" ");
				}
			}
	}
}

void GraphicalDisplay::generateBoard() {
	// Clearing the grid:
	for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 18; j++) {
				buttonBoardGrid.at(i).at(j)->set_label(" ");
			}
	}

	// Remaking the grid:
	std::vector <std::vector <std::pair<BlockType, int>>> curGrid = getBoardModel()->getGrid(); // the current grid

	  // Get cell information of current block
	  std::shared_ptr<GenericBlock> curBlock = getBoardModel()->getCurBlock();
	  int r = curBlock->getRotation();
	  std::pair <int, int> baseCoords = curBlock->getCoords();
	  std::pair <int, int> cell0 = curBlock->getCells().at(r).at(0);
	  std::pair <int, int> cell1 = curBlock->getCells().at(r).at(1);
	  std::pair <int, int> cell2 = curBlock->getCells().at(r).at(2);
	  std::pair <int, int> cell3 = curBlock->getCells().at(r).at(3);

	  // Get cell information of hint block, if it exists
	  std::shared_ptr<GenericBlock> hintBlock = getBoardModel()->getHintBlock();
	  int hintR = hintBlock != nullptr ? hintBlock->getRotation() : -1;
	  std::pair <int, int> hintBaseCoords = hintBlock != nullptr ? hintBlock->getCoords() : std::make_pair(-1,-1);
	  std::pair <int, int> hintCell0 = hintBlock != nullptr ? hintBlock->getCells().at(hintR).at(0) : std::make_pair(-1,-1);
	  std::pair <int, int> hintCell1 = hintBlock != nullptr ? hintBlock->getCells().at(hintR).at(1) : std::make_pair(-1,-1);
	  std::pair <int, int> hintCell2 = hintBlock != nullptr ? hintBlock->getCells().at(hintR).at(2) : std::make_pair(-1,-1);
	  std::pair <int, int> hintCell3 = hintBlock != nullptr ? hintBlock->getCells().at(hintR).at(3) : std::make_pair(-1,-1);

	  for(std::size_t i = 0; i < curGrid.size(); ++i) {
	    for(std::size_t j = 0; j < curGrid.at(i).size(); ++j){
	      if (((int)j == baseCoords.first+cell0.first && 18-1-(int)i == baseCoords.second+cell0.second) ||
	          ((int)j == baseCoords.first+cell1.first && 18-1-(int)i == baseCoords.second+cell1.second) ||
	          ((int)j == baseCoords.first+cell2.first && 18-1-(int)i == baseCoords.second+cell2.second) ||
	          ((int)j == baseCoords.first+cell3.first && 18-1-(int)i == baseCoords.second+cell3.second)) {
	        // current block
	    	buttonBoardGrid.at(i).at(j)->set_label(blockTypeToColour_.at(curBlock->getType()));
	      } else if (((int)j == hintBaseCoords.first+hintCell0.first && 18-1-(int)i == hintBaseCoords.second+hintCell0.second) ||
	                 ((int)j == hintBaseCoords.first+hintCell1.first && 18-1-(int)i == hintBaseCoords.second+hintCell1.second) ||
	                 ((int)j == hintBaseCoords.first+hintCell2.first && 18-1-(int)i == hintBaseCoords.second+hintCell2.second) ||
	                 ((int)j == hintBaseCoords.first+hintCell3.first && 18-1-(int)i == hintBaseCoords.second+hintCell3.second)) {
	        // hint block
	    	  buttonBoardGrid.at(i).at(j)->set_label(blockTypeToColour_.at(hintBlock->getType()));
	      } else {
	        // other blocks
	         buttonBoardGrid.at(i).at(j)->set_label(blockTypeToColour_.at(getBoardModel()->getCell(j, 18-1-i).first));

	      }
	    }
	  }
}
