//
// Created by oem on 15/01/2020.
//

#ifndef EXX4_DFS_H
#define EXX4_DFS_H

#include "CommonSearcher.h"
#include <iostream>
#include <algorithm>
#include "stack"

using namespace std;

template<class T, class solution>
class DFS : public CommonSearcher<solution, T> {
private:
    int numEvaluatedNodes = 0;
public:
    /**
    /** looking for a path to the given goal state with the smallest cost **/
    solution search(Searchable<T> *searchable) override {
        numEvaluatedNodes = 0;
        vector<State<T> *> visited;
        // we use a stack so we will get the last element we entered
        stack<State<T> *> openStack;
        this->setSearchable(searchable);
        State<T> *startState = this->getSearchable()->getInitialeState();

       // visited.push_back(startState);
        openStack.push(startState);
        while (openStack.size() > 0) {

            State<T> *curState = openStack.top();
            openStack.pop();
            // updating the number of states we visited in
            numEvaluatedNodes++;
            visited.push_back(curState);

            // ending condition to the recursion
            if ((*curState).Equals((this->getSearchable())->getGoalState())) {
                return this->backTrace(curState);
            }
            // entering the successors to the priority list too
            list<State<T> *> successors = (this->getSearchable())->createSuccessors(curState);
            for (State<T> *n: successors) {
                if (this->getDirection(n, curState) == "") {
                    cout<< "error"<<endl;
                }
                if (!checkIfVisitedContains(visited, n)) {
                    n->setCameFRom(curState);
                    n->setTrailCost(curState->getTrailCost() + n->getCost());
                    openStack.push(n);
                    visited.push_back(n);
                }
            }
        }
        // if there is no solution
        throw "no solution";
    }

    /** iterating over the visited vector in order to see if a certain state is already in it**/
    bool checkIfVisitedContains(vector<State<T> *> visited, State<T> *curState) {
        for (auto it = visited.begin(); it != visited.end(); ++it) {
            if (curState->Equals(*it)) {
                return true;
            }
        }
        return false;
    }

    /**clone **/
    DFS *copy() {
        return new DFS();
    }

    /** returns the number of nodes we visited in the algorithm**/
    int getNumberOfNodesEvaluated() override {
        return this->numEvaluatedNodes;
    }
};

#endif //EXX4_DFS_H
