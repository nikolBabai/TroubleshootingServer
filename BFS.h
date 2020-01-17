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

template<class T, class solution>
class BFS : public CommonSearcher<solution, T> {
private:
   int evaluatedNodes = 0;
public:
    solution search(Searchable<T> *searchable) override {
        // fields
        vector<State<T> *> visited;
        stack<State<T> *> openPriority_stack;

        this->setSearchable(searchable);
        visited.push_back(searchable->getInitialeState());
        openPriority_stack.push(searchable->getInitialeState());
        while (!openPriority_stack.empty()) {
            State<T> *curState = openPriority_stack.top();
            if ((*curState).Equals(searchable->getGoalState())) {
                return this->backTrace(curState);
            }
            openPriority_stack.pop();
            // entering the successors to the priority list too
            list<State<T> *> successors = searchable->createSuccessors(curState);
            for (State<T> *n: successors) {
                auto iter = find(visited.begin(), visited.end(), n);
                // if we didn't visit in this state before
                if (iter == visited.end()) {
                    visited.push_back(n);
                    openPriority_stack.push(n);
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


    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }};

#endif //EXX4_BFS_H

#endif //EXX4_BFS_H
