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
                return backtrace();
            }
            this->openPriority_queue.pop();
            list<State<T> *> successors = searchable->createSuccessors(searchable->getInitialeState());
            for (State<T> * n: successors) {
               auto iter = find(visited.begin(),visited.end(), n);
                if (iter!=visited.end()) {
                    visited.push_back(n);
                    this->openPriority_queue.push(n);
                    n->setCameFRom(curState);
                    n->setCost(curState->getCost()+1);
                }
            }
    }
}
string backtrace() {
    State<T>* curState=this->getSearchable()->getGoalState();
    string *line = new string("");
        while((*curState).Equals(this->searchable1->getGoalState())) {
            *line += getDirection(curState, curState->getCameFRom()) + ",";
            curState = curState->getCameFRom();
        }
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
};
#endif //EXX4_BFS_H
