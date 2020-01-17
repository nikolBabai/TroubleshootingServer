//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_SEARCHER_H
#define EXX4_SEARCHER_H

#include "Searchable.h"

template<class solution, class T>
class Searcher {
private:
    Searchable<T> *searchable1;
public:
    virtual solution search(Searchable<T> *searchable) = 0;
    virtual Searcher* copy()=0;
    virtual int getNumberOfNodesEvaluated() = 0;

    Searchable<T> *getSearchable() {
        return searchable1;
    };

    void setSearchable(Searchable<T> *searchableIn) {
         this->searchable1 = searchableIn;
    };
};

#endif //EXX4_SEARCHER_H
