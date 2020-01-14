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
    class MyComperator {
    public:
        bool operator()(State<T> *left, State<T> *right) {
            return (left->getCost()) > (right->getCost());
        }
    };
protected:
    priority_queue<State<T> *, vector<State<T> *>, MyComperator> openPriority_queue;
    Searchable<T> *searchable1;
    int evaluatedNodes = 0;
public:
    CommonSearcher() {}

    virtual solution search(Searchable<T> *searchable) = 0;


    void setSearchable(Searchable<T>* searchableIN) {
        this->searchable1 = searchableIN;
    }

    Searchable<T>* getSearchable() {
        return this->searchable1;
    };

    virtual ~CommonSearcher() {}

    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }

    priority_queue<State<T> *, vector<State<T> *>, MyComperator>
    updatePriorityQueqe(priority_queue<State<T> *, vector<State<T> *>, MyComperator> enteredQueqe) {
        priority_queue<State<T> *, vector<State<T> *>, MyComperator> newQueqe;
        while (enteredQueqe.size() > 0) {
            newQueqe.push(enteredQueqe.top());
            enteredQueqe.pop();
        }
        return newQueqe;
    }
};

#endif //EXX4_COMMONSEARCHER_H
