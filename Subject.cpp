// Subject.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include <set>
#include "Subject.h"
#include "observer.h"

void Subject::subscribe(Observer *newObserver){
  observers_.insert(newObserver);
}

void Subject::unsubscribe(Observer* oldObserver){
  observers_.erase(oldObserver);
}

void Subject::notify(){
  Observers::iterator it;
  for (it = observers_begin(); it != observers_end(); it++){
	(*it)->update();
  }
}
