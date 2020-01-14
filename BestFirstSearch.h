//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_BESTFIRSTSEARCH_H
#define EXX4_BESTFIRSTSEARCH_H

#include "CommonSearcher.h"

template<class T>
class BestFirstSearch : public CommonSearcher<string, T> {
    class MyComperator {
    public:
        bool operator()(State<T> *left, State<T> *right) {
            return (left->getCost()) > (right->getCost());
        }
    };

private:
    priority_queue<State<T> *, vector<State<T> *>, MyComperator> openPriority_queue;
    vector<State<T> *> closed;
    vector<State<T> *> statesInOpenPriority;

public:

    int openListSize() {
        return openPriority_queue.size();
    }

    void addToOpenList(State<T> *state) {
        openPriority_queue.push(state);
        statesInOpenPriority.push_back(state);
    }

    State<T> *popOpenList() {
        this->evaluatedNodes++;
        State<T> *topItem = openPriority_queue.top();
        openPriority_queue.pop();
        return topItem;
    }

    bool openContaines(State<T> *state) {
        for (auto n: statesInOpenPriority) {
            if (state->Equals(n)) {
                return true;
            }
        }
        return false;
    }

    string search(Searchable<T> *searchable) {
        this->setSearchable(searchable);
        addToOpenList(searchable->getInitialeState());
        while (this->openListSize() > 0) {
            State<T> *n = this->popOpenList();
            closed.push_back(n);
            if ((*n).Equals(searchable->getGoalState())) {
                // return the steps we did to get to this goal
                return backTrace(n);
            }
            // createSuccessors(n) returns a list of states with n as a parent
            list<State<T> *> successors = searchable->createSuccessors(n);
            for (State<T> *s : successors) {
                if (!(closedCOntaines(s)) && !this->openContaines(s)) {
                    s->setCameFRom(n);
                    s->setTrailCost(n->getTrailCost() + s->getCost());
                    addToOpenList(s);
                } else {
                    // check if the path from n is better than the old path
                    double sTrailCost = s->getTrailCost();
                    double errowToState = s->getCost();
                    double newTrailCost = n->getTrailCost() + errowToState;
                    if (newTrailCost < sTrailCost) {
                        if (!this->openContaines(s)) {
                            // adding to open list
                            addToOpenList(s);
                        } else {
                            // updating the cameFrom
                            s->setCameFRom(n);
                            s->setTrailCost(newTrailCost);
                            openPriority_queue = updatePriorityQueqe(openPriority_queue);
                        }

                    }
                }
            }
        }

    }

    bool closedCOntaines(State<T> *s) {
        for (auto n: closed) {
            if (s->Equals(n)) {
                return true;
            }
        }
        return false;
    }

    string backTrace(State<T> *step) {
        // return the steps we did to get to this goal
        string solutionMatrix = "";
        State<T> *start = this->getSearchable()->getInitialeState();
        // State<T> *step = this->getSearchable()->getGoalState();
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


#endif //EXX4_BESTFIRSTSEARCH_H
