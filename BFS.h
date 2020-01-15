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
    vector<State<T>*> visited;
public:
    string search(Searchable<T> *searchable) override {
        this->setSearchable(searchable);
        visited.push_back(searchable->getInitialeState());
        this->openPriority_queue.push(searchable->getInitialeState());
        while(!this->openPriority_queue.empty()) {
            State<T>* curState= this->openPriority_queue.top();
            if ((*curState).Equals(searchable->getGoalState())) {
                return this->backTrace(curState);
            }
            this->openPriority_queue.pop();
            // entering the successors to the priority list too
            list<State<T> *> successors = searchable->createSuccessors(curState);
            for (State<T> * n: successors) {
               auto iter = find(visited.begin(),visited.end(), n);
               // if we didn't visit in this state before
                if (iter==visited.end()) {
                    visited.push_back(n);
                    this->openPriority_queue.push(n);
                    n->setCameFRom(curState);
                    // updating the number of states we visited in
                    this->evaluatedNodes++;
                   // n->setCost(curState->getCost()+1);
                }
            }
    }
}
/*
    string backTrace(State<T> *step) {
        // return the steps we did to get to this goal
        string solutionMatrix = "";
        State<T> *start = this->getSearchable()->getInitialeState();
        // checking if we arrived to the start state
        while (!step->Equals(start)) {
            State<T> *prev = step->getCameFRom();
            string s = getDirection(step, prev);
            solutionMatrix = s + solutionMatrix;
            solutionMatrix = ", " + solutionMatrix;
            step = step->getCameFRom();
        }
        solutionMatrix = &solutionMatrix[2];
        return solutionMatrix;
    }
/*
string backtrace(State<T>* curState) {
    string line = "";
        while(!(*curState).Equals(this->searchable1->getInitialeState())) {
            line = getDirection(curState, curState->getCameFRom()) + line;
            line = "," + line;
            curState = curState->getCameFRom();
        }
        line = &line[2];
        return line;
    }

    string getDirection(State<T> *step, State<T> *prev) {
        std::pair<int, int> stepDirection = this->searchable1->getLocationInSearchable(step);
        std::pair<int, int> prevDirection = this->searchable1->getLocationInSearchable(prev);

        int xStep = stepDirection.first;
        int yStep = stepDirection.second;
        int xPrev = prevDirection.first;
        int yPrev = prevDirection.second;

        // checking the direction it came from
        if (xStep > xPrev) {
            return "Down";
        } else if (xStep < xPrev) {
            return "Up";
        } else if (yStep > yPrev) {
            return "Right";
        } else if (yStep > yPrev) {
            return "Left";
        }
    }
    */
};
#endif //EXX4_BFS_H
