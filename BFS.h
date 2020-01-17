//
// Created by oem on 15/01/2020.
//

#ifndef EXX4_BFS1_H
#define EXX4_BFS1_H
//
// Created by oem on 14/01/2020.
//

#ifndef EXX4_BFS_H
#define EXX4_BFS_H

#include "CommonSearcher.h"
#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
class BFS : public CommonSearcher<string, T> {
private:
    vector<State<T> *> visited;
public:
    string search(Searchable<T> *searchable) override {
        this->setSearchable(searchable);
        visited.push_back(searchable->getInitialeState());
        this->openPriority_queue.push(searchable->getInitialeState());
        while (!this->openPriority_queue.empty()) {
            State<T> *curState = this->openPriority_queue.top();
            if ((*curState).Equals(searchable->getGoalState())) {
                return this->backTrace(curState);
            }
            this->openPriority_queue.pop();
            // entering the successors to the priority list too
            list<State<T> *> successors = searchable->createSuccessors(curState);
            for (State<T> *n: successors) {
                auto iter = find(visited.begin(), visited.end(), n);
                // if we didn't visit in this state before
                if (iter == visited.end()) {
                    visited.push_back(n);
                    this->openPriority_queue.push(n);
                    n->setCameFRom(curState);
                    n->setTrailCost(curState->getTrailCost() + n->getCost());
                    // updating the number of states we visited in
                    this->evaluatedNodes++;
                }
            }
        }
        // if there is no solution
        return "";
    }
    void* copy() {
        return new BFS();
    }
};

#endif //EXX4_BFS_H

#endif //EXX4_BFS_H
