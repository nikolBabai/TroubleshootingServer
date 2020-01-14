//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_SEARCHER_H
#define EXX4_SEARCHER_H

#include "Searchable.h"

template<class solution, class T>
class Searcher {
public:
    virtual solution search(Searchable<T> *searchable) = 0;

    int getNumberOfNodesEvaluated();

    Searchable<T> *getSearchable1() {
        return this->searchable1;
    };
};

#endif //EXX4_SEARCHER_H
