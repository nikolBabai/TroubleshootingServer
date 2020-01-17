//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_SEARCHABLE_H
#define EXX4_SEARCHABLE_H

#include "State.h"
#include <list>

template<class T>
class Searchable {
public:
    virtual State<T>* getInitialeState() = 0;

    virtual State<T>* getGoalState() = 0;

    virtual list<State<T>*> createSuccessors(State<T>* s) = 0;

    virtual bool isGoal(State<T> *s) = 0;

    virtual std::pair<int, int> getLocationInSearchable(State<T> *state) = 0;

    virtual Searchable* copy()=0;
};

#endif //EXX4_SEARCHABLE_H
