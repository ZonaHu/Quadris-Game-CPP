//
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.


#include "TextDisplay.h"

#include <utility>

TextDisplay::TextDisplay(std::ostream &o, std::shared_ptr<BoardModel> boardModel):ost_{o}, boardModel_{std::move(boardModel)} {}

TextDisplay::~TextDisplay() {
  //call unsubscribe in the destructor
  boardModel_->unsubscribe(this);
}

void TextDisplay::update(std::shared_ptr <Subject>) {



}


/*std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  return <#initializer #>;
}*/
