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
        vector<State<T> *> visited;
        stack<State<T>*> openStack;
        this->setSearchable(searchable);

        visited.push_back(searchable->getInitialeState());
        openStack.push(searchable->getInitialeState());
        while (!openStack.empty()) {
            State<T> *curState = openStack.top();
            openStack.pop();
            this->evaluatedNodes++;
            evaluatedNodes++;

            if ((*curState).Equals(searchable->getGoalState())) {
                return this->backTrace(curState);
            }

            // entering the successors to the priority list too
            list<State<T> *> successors = searchable->createSuccessors(curState);
            for (State<T> *n: successors) {
                auto iter = find(visited.begin(), visited.end(), n);
                // if we didn't visit in this state before
                if (iter == visited.end()) {
                    visited.push_back(n);
                    openStack.push(n);
                    n->setCameFRom(curState);
                    n->setTrailCost(curState->getTrailCost() + n->getCost());
                }
            }
        }
        // if there is no solution
        return "";
    }
   BFS* copy() {
        return new BFS();
    }

    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }
};

#endif //EXX4_BFS_H

#endif //EXX4_BFS_H
