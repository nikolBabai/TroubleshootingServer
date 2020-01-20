//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_BESTFIRSTSEARCH_H
#define EXX4_BESTFIRSTSEARCH_H

#include "CommonSearcher.h"

/** searching algorithm - Best First Search uses an evaluation function to decide which adjacent is most
 * promising and then explore. **/
template<class T, class solution>
class BestFirstSearch : public CommonSearcher<solution, T> {
public:
    class MyComperator {
    public:
        bool operator()(State<T> *left, State<T> *right) {
            return (left->getTrailCost()) > right->getTrailCost();
        }

        virtual ~MyComperator() = default;
    };

private:
    int evaluatedNodes = 0;
public:
    /** entering a node to the priority queue and the vector**/
    void
    addToOpenList(State<T> *state, priority_queue<State<T> *, vector<State<T> *>, MyComperator> *openPriority_queue,
                  vector<State<T> *> *statesInOpenPriority) {
        openPriority_queue->push(state);
        statesInOpenPriority->push_back(state);
    }

    /** removing from the open list because we finished processing this node's information**/
    State<T> *popOpenList(priority_queue<State<T> *, vector<State<T> *>, MyComperator> *openPriority_queue) {
        this->evaluatedNodes++;
        State<T> *topItem = openPriority_queue->top();
        openPriority_queue->pop();
        return topItem;
    }

    /** checking if a state is in the vector (meaning in the open priority queue)**/
    bool openContaines(State<T> *state, vector<State<T> *> statesInOpenPriority) {
        for (auto n: statesInOpenPriority) {
            if (state->Equals(n)) {
                return true;
            }
        }
        return false;
    }

    /** looking for a path to the given goal state with the smallest cost **/
    solution search(Searchable<T> *searchable) {
        evaluatedNodes = 0;
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
        throw "no solution";
    }

    /** checking if a state is in the closed vector**/
    bool closedCOntaines(State<T> *s, vector<State<T> *> closed) {
        for (auto n: closed) {
            if (s->Equals(n)) {
                return true;
            }
        }
        return false;
    }

    /** returns the number of nodes we visited in the algorithm**/
    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }

    /** updating the priority queue**/
    priority_queue<State<T> *, vector<State<T> *>, MyComperator>
    updatePriorityQueqe(priority_queue<State<T> *, vector<State<T> *>, MyComperator> enteredQueqe) {
        priority_queue<State<T> *, vector<State<T> *>, MyComperator> newQueqe;
        while (enteredQueqe.size() > 0) {
            newQueqe.push(enteredQueqe.top());
            enteredQueqe.pop();
        }
        return newQueqe;
    }

    /** clone **/
    BestFirstSearch *copy() {
        return new BestFirstSearch();
    }
};


#endif //EXX4_BESTFIRSTSEARCH_H
