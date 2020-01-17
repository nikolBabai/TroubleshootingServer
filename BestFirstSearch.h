//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_BESTFIRSTSEARCH_H
#define EXX4_BESTFIRSTSEARCH_H

#include "CommonSearcher.h"

template<class T, class solution>
class BestFirstSearch : public CommonSearcher<solution, T> {
public:
    class MyComperator {
    public:
        bool operator()(State<T> *left, State<T> *right) {
            return (left->getTrailCost()) > right->getTrailCost();
        }
    };
private:
    int evaluatedNodes = 0;
    /**
    priority_queue<State<T> *, vector<State<T> *>, MyComperator> openPriority_queue;
    vector<State<T> *> closed;
    vector<State<T> *> statesInOpenPriority;
     **/
public:
    /**
    int openListSize() {
        return this->openPriority_queue.size();
    }**/

    void addToOpenList(State<T> *state, priority_queue<State<T> *, vector<State<T> *>, MyComperator> *openPriority_queue, vector<State<T> *> *statesInOpenPriority) {
        openPriority_queue->push(state);
        statesInOpenPriority->push_back(state);
    }

    State<T> *popOpenList(priority_queue<State<T> *, vector<State<T> *>, MyComperator> *openPriority_queue) {
        this->evaluatedNodes++;
        State<T> *topItem = openPriority_queue->top();
        openPriority_queue->pop();
        return topItem;
    }

    bool openContaines(State<T> *state, vector<State<T> *> statesInOpenPriority) {
        for (auto n: statesInOpenPriority) {
            if (state->Equals(n)) {
                return true;
            }
        }
        return false;
    }

    solution search(Searchable<T> *searchable) {
        // fields
        priority_queue<State<T> *, vector<State<T> *>, MyComperator> openPriority_queue;
       // int evaluatedNodes = 0;
        vector<State<T> *> closed;
        vector<State<T> *> statesInOpenPriority;

        this->setSearchable(searchable);
        addToOpenList(searchable->getInitialeState(), &openPriority_queue, &statesInOpenPriority);
        while (openPriority_queue.size() > 0) {
            State<T> *n = this->popOpenList(&openPriority_queue);
            closed.push_back(n);
            if ((*n).Equals(searchable->getGoalState())) {
                // return the steps we did to get to this goal
                return this->backTrace(n);
            }
            // createSuccessors(n) returns a list of states with n as a parent
            list<State<T> *> successors = searchable->createSuccessors(n);
            for (State<T> *s : successors) {
                if (!(closedCOntaines(s, closed)) && !openContaines(s, statesInOpenPriority)) {
                    s->setCameFRom(n);
                    s->setTrailCost(n->getTrailCost() + s->getCost());
                    addToOpenList(s, &openPriority_queue, &statesInOpenPriority);
                } else {
                    // check if the path from n is better than the old path
                    double sTrailCost = s->getTrailCost();
                    double errowToState = s->getCost();
                    double newTrailCost = n->getTrailCost() + errowToState;
                    if (newTrailCost < sTrailCost) {
                        if (!openContaines(s, statesInOpenPriority)) {
                            // adding to open list
                            addToOpenList(s, &openPriority_queue, &statesInOpenPriority);
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
        // if there is no solution
        return "";
    }

    bool closedCOntaines(State<T> *s, vector<State<T> *> closed) {
        for (auto n: closed) {
            if (s->Equals(n)) {
                return true;
            }
        }
        return false;
    }

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
   BestFirstSearch* copy() {
        return new BestFirstSearch();
    }
};


#endif //EXX4_BESTFIRSTSEARCH_H
