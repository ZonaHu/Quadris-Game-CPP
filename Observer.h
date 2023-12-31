// File: Observer.h
//
// Created by Simran Thind, Janakitti Ratana-Rueangsri, Zuomiao Hu
// on 2021-07-16.

#ifndef PROJECT_2_3_OBSERVER_H
#define PROJECT_2_3_OBSERVER_H
#include <memory>

class Subject;

class Observer{
public:
  virtual ~Observer(){}; // destructor
  virtual void update() = 0;
};

#endif // PROJECT_2_3_OBSERVER_H
