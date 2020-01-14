//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_COMMONSEARCHER_H
#define EXX4_COMMONSEARCHER_H

#include "Searcher.h"
#include "queue"
#include "unordered_set"

//#include "Point.h"

using namespace std;

template<class solution, class T>
class CommonSearcher : public Searcher<solution, T> {
protected:
    Searchable<T> *searchable1;
    int evaluatedNodes = 0;
public:
    CommonSearcher() {}

    virtual solution search(Searchable<T> *searchable) = 0;

    int getNUmberOfEvaluatedNOdes() {
        return this->evaluatedNodes;
    }

    void setSearchable(Searchable<T>* searchableIN) {
        this->searchable1 = searchableIN;
    }

    Searchable<T>* getSearchable() {
        return this->searchable1;
    };

    virtual ~CommonSearcher() {}
};

#endif //EXX4_COMMONSEARCHER_H
