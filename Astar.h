//
// Created by osboxes on 1/15/20.
//

#ifndef EXX4_ASTAR_H
#define EXX4_ASTAR_H

#include "CommonSearcher.h"

template<typename T, typename solution>
class Astar : public CommonSearcher<solution, T> {

    class ComparatorAStar : CommonSearcher<solution, T>::Comperator {
    public:
        virtual bool operator()(State<T> *left, State<T> *right) {
            double F_L = left->getTrailCost() + left->getHuristic();
            double F_R = right->getTrailCost() + right->getHuristic();
            return F_L > F_R;
        }

    private:
        priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> openPriority_queue;
        vector<State<T> *> closed;
        vector<State<T> *> openCopy;
    public:
        solution search(Searchable<T> *searchable) override {
            State<T> *startState = searchable->getInitialeState();
            State<T> *goalState = searchable->getGoalState();
            //push the init state to queue
            openPriority_queue.push(startState);
            openCopy.push(startState);
            while (this->openPriority_queue.empty()) {
                //current is start state
                State<T> *currentState = this->openPriority_queue.top();
                openPriority_queue.pop();
                openCopy.erase(currentState);
                this->evaluatedNodes++;
                if ((*currentState).Equals(searchable->getGoalState())) {
                    return this->backTrace(currentState);

                }
                this->closed.insert(currentState);
                vector<State<T> *> neighbours = searchable->createSuccessors(currentState);
                for (State<T> *neighbour: neighbours) {
                    double Possible_Trail = currentState->getTrailCost() + neighbour->getCost();
                    if (!dataContaines(openCopy,neighbour)&& !dataContaines(closed,neighbour)){

                    }
                }
            }
        }
        bool dataContaines(vector<State<T>*>* data,State<T> *state) {
            for (auto n: data) {
                if (state->Equals(n)) {
                    return true;
                }
            }
            return false;
        }
    };

};

#endif //EXX4_ASTAR_H
