// Subject.cpp
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#include <set>
#include "Subject.h"
#include "Observer.h"

void Subject::subscribe(std::shared_ptr<Observer> newObserver){
  observers_.insert(newObserver);
}

void Subject::unsubscribe(Observer* oldObserver){
  // observers_.erase(oldObserver);
}

void Subject::notify(){
   // the notify function calls update in all subscribed observers
   Observers::iterator it;
   for (it = observers_.begin(); it != observers_.end(); it++){
     (*it)->update();
   }
}
