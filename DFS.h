//
// Created by oem on 15/01/2020.
//

#ifndef EXX4_DFS_H
#define EXX4_DFS_H

#include "CommonSearcher.h"
#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
class DFS : public CommonSearcher<string, T> {
private:
    vector<State<T> *> visited;
public:
    string search(Searchable<T> *searchable) override {
        this->setSearchable(searchable);
        State<T> *startState = this->getSearchable()->getInitialeState();
        return DfsUtil(visited, startState);
    }

    string DfsUtil(vector<State<T> *> visited, State<T> *curState) {
        string line = "";
        visited.push_back(curState);
        this->openPriority_queue.push(curState);

        // updating the number of states we visited in
        this->evaluatedNodes++;

        // ending condition to the recursion
        if ((*curState).Equals(this->getSearchable()->getGoalState())) {
            line = this->backTrace(curState);
            return line;
        }
        this->openPriority_queue.pop();
        // entering the successors to the priority list too
        list<State<T> *> successors = this->getSearchable()->createSuccessors(curState);
        for (State<T> *n: successors) {
            if (!checkIfVisitedContains(visited, n)) {
                n->setCameFRom(curState);
                n->setTrailCost(curState->getTrailCost() + n->getCost());
                line = DfsUtil(visited, n);
                if (line != "") {
                    return line;
                }
            }
        }
        return line;
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
};

#endif //EXX4_DFS_H
