// Subject.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_SUBJECT_H
#define PROJECT_2_3_SUBJECT_H
#include <algorithm>
#include <set>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Observer.h"

typedef std::set<std::shared_ptr <Observer>> Observers;

class Subject {
private:
  Observers  observers_; // set of subscribed observers

protected:
  void notify();  //Notify subscribed observers of update

public:
  Subject()= default; // default constructor
  ~Subject()= default; // default destructor
  void subscribe(std::shared_ptr <Observer>);    //Add referenced observer to set of observers
  void unsubscribe(std::shared_ptr <Observer>);   //Remove referenced observer to set of observers
};

#endif // PROJECT_2_3_SUBJECT_H
