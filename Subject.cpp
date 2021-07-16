// Subject.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include "Subject.h"

void Subject::subscribe(Observer *newObserver){
  observers_.insert(newObserver);
}

void Subject::unsubscribe(Observer* oldObserver){
  observers.erase(oldObserver);
}

void Subject::notify(){
  //TODO; implement this

}
