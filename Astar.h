//
// Created by osboxes on 1/15/20.
//

#ifndef EXX4_ASTAR_H
#define EXX4_ASTAR_H

#include "CommonSearcher.h"
#include <algorithm>

template<typename T>
class Astar : public CommonSearcher<string, T> {

    class ComparatorAStar : CommonSearcher<string, T>::MyComperator {
    public:
        virtual bool operator()(State<T> *left, State<T> *right) {
            double F_L = left->getTrailCost() + left->getHeuristic();
            double F_R = right->getTrailCost() + right->getHeuristic();
            return F_L > F_R;
        }
    };

private:
    priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> openPriority_queue;
    vector<State<T> *> closed;
    vector<State<T> *> openCopy;
public:
    string search(Searchable<T> *searchable) override {
        this->setSearchable(searchable);
        State<T> *startState = searchable->getInitialeState();
        State<T> *goalState = searchable->getGoalState();
        //push the init state to queue
        enterToOpen(startState);
        while (!this->openPriority_queue.empty()) {
            //current is start state
            State<T> *currentState = this->openPriority_queue.top();
            openPriority_queue.pop();
            deleteFromOpen(currentState);
            this->evaluatedNodes++;
            if ((*currentState).Equals(searchable->getGoalState())) {
                return this->backTrace(currentState);
            }
            this->closed.push_back(currentState);
            list<State<T> *> neighbours = searchable->createSuccessors(currentState);
            for (State<T> *neighbour: neighbours) {
                double possible_Trail = currentState->getTrailCost() + neighbour->getCost();
                if (!dataContaines(openCopy, neighbour) && !dataContaines(closed, neighbour)) {
                    notInOpenClose(neighbour, currentState, possible_Trail);
                    continue;
                } else if (possible_Trail < neighbour->getTrailCost()) {
                    improvePath(neighbour, currentState, possible_Trail);
                    continue;
                }
            }
        }
        // if there is no solution
        return "";
    }

    void improvePath(State<T> *neighbour, State<T> *currentState, double possible_Trail) {
        State<T> *goalState = this->getSearchable()->getGoalState();
        neighbour->setCameFRom(currentState);
        neighbour->setTrailCost(possible_Trail);
        setHeuristic(neighbour, goalState);
        openPriority_queue = updatePriorityQueqe(openPriority_queue);
    }

    void notInOpenClose(State<T> *neighbour, State<T> *currentState, double possible_Trail) {
        State<T> *goalState = this->getSearchable()->getGoalState();
        neighbour->setCameFRom(currentState);
        neighbour->setTrailCost(possible_Trail);
        setHeuristic(neighbour, goalState);
        enterToOpen(neighbour);
    }

    void enterToOpen(State<T> *neighbour) {
        openPriority_queue.push(neighbour);
        openCopy.push_back(neighbour);
    }

    bool dataContaines(vector<State<T> *> data, State<T> *state) {
        for (auto n: data) {
            if (state->Equals(n)) {
                return true;
            }
        }
        return false;
    }

    void deleteFromOpen(State<T> *cur) {
        auto position = find(openCopy.begin(), openCopy.end(), cur);
        if (position != openCopy.end()) {// == myVector.end() means the element was not found
            openCopy.erase(position);
        }
    }

    void setHeuristic(State<T> *neighbour, State<T> *goalState) {
        std::pair<int, int> direction = this->getSearchable()->getLocationInSearchable(neighbour);

        int X_Neighbour = direction.first;
        int Y_Neighbour = direction.second;
        direction = this->getSearchable()->getLocationInSearchable(goalState);
        int X_Goal = direction.first;
        int Y_Goal = direction.second;
        neighbour->setHeuristic(abs(X_Goal - X_Neighbour) + abs(Y_Goal - Y_Neighbour));


    }

    priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar>
    updatePriorityQueqe(priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> enteredQueqe) {
        priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> newQueqe;
        while (enteredQueqe.size() > 0) {
            newQueqe.push(enteredQueqe.top());
            enteredQueqe.pop();
        }
        return newQueqe;
    }

};

#endif //EXX4_ASTAR_H
