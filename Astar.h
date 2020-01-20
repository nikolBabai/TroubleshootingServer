//
// Created by osboxes on 1/15/20.
//

#ifndef EXX4_ASTAR_H
#define EXX4_ASTAR_H

#include "CommonSearcher.h"
#include <algorithm>

/** starting from a specific starting state of a matrix, it aims to find a path to the given goal state having the
 * smallest cost (least distance travelled, shortest time, etc.)**/
template<class T, class solution>
class Astar : public CommonSearcher<solution, T> {

    class ComparatorAStar {
    public:
        virtual bool operator()(State<T> *left, State<T> *right) {
            double F_L = left->getTrailCost() + left->getHeuristic();
            double F_R = right->getTrailCost() + right->getHeuristic();
            return F_L > F_R;
        }
    };

private:
    int evaluatedNodes = 0;
public:
    /** looking for a path to the given goal state with the smallest cost **/
    solution search(Searchable<T> *searchable) override {
        evaluatedNodes = 0;
        // fields
        priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> openPriority_queue;
        vector<State<T> *> closed;
        vector<State<T> *> openCopy;

        this->setSearchable(searchable);
        State<T> *startState = searchable->getInitialeState();
        State<T> *goalState = searchable->getGoalState();
        //push the init state to queue
        enterToOpen(startState, &openPriority_queue, &openCopy);
        while (!openPriority_queue.empty()) {
            //current is start state
            State<T> *currentState = openPriority_queue.top();
            openPriority_queue.pop();
            deleteFromOpen(currentState, &openCopy);
            this->evaluatedNodes++;
            if ((*currentState).Equals(searchable->getGoalState())) {
                return this->backTrace(currentState);
            }
            closed.push_back(currentState);
            list<State<T> *> neighbours = searchable->createSuccessors(currentState);
            for (State<T> *neighbour: neighbours) {
                double possible_Trail = currentState->getTrailCost() + neighbour->getCost();
                if (!dataContaines(openCopy, neighbour) && !dataContaines(closed, neighbour)) {
                    notInOpenClose(neighbour, currentState, possible_Trail, &openPriority_queue, &openCopy);
                    continue;
                } else if (possible_Trail < neighbour->getTrailCost()) {
                    // checking for an improvement
                    improvePath(neighbour, currentState, possible_Trail, &openPriority_queue);
                    continue;
                }
            }
        }
        // if there is no solution
        throw "no solution";
    }

    /** returns the number of nodes we visited in the algorithm**/
    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }

    /** improving the path by changing the came from state of a node**/
    void improvePath(State<T> *neighbour, State<T> *currentState, double possible_Trail,
                     priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> *openPriority_queue) {
        State<T> *goalState = this->getSearchable()->getGoalState();
        neighbour->setCameFRom(currentState);
        neighbour->setTrailCost(possible_Trail);
        setHeuristic(neighbour, goalState);
        *openPriority_queue = updatePriorityQueqe(*openPriority_queue);
    }

    /** initializing a node after checking it's not in any vector/ priority queue**/
    void notInOpenClose(State<T> *neighbour, State<T> *currentState, double possible_Trail,
                        priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> *openPriority_queue,
                        vector<State<T> *> *openCopy) {
        State<T> *goalState = this->getSearchable()->getGoalState();
        neighbour->setCameFRom(currentState);
        neighbour->setTrailCost(possible_Trail);
        setHeuristic(neighbour, goalState);
        enterToOpen(neighbour, openPriority_queue, openCopy);
    }

    /** entering a node to the priority queue**/
    void enterToOpen(State<T> *neighbour,
                     priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> *openPriority_queue,
                     vector<State<T> *> *openCopy) {
        openPriority_queue->push(neighbour);
        openCopy->push_back(neighbour);
    }

    /** checking if a state is in the vector**/
    bool dataContaines(vector<State<T> *> data, State<T> *state) {
        for (auto n: data) {
            if (state->Equals(n)) {
                return true;
            }
        }
        return false;
    }

    /** *removing a node from the vector*/
    void deleteFromOpen(State<T> *cur, vector<State<T> *> *openCopy) {
        auto position = find(openCopy->begin(), openCopy->end(), cur);
        if (position != openCopy->end()) {// == myVector.end() means the element was not found
            openCopy->erase(position);
        }
    }

    /** setting heuristic**/
    void setHeuristic(State<T> *neighbour, State<T> *goalState) {
        std::pair<int, int> direction = this->getSearchable()->getLocationInSearchable(neighbour);

        int X_Neighbour = direction.first;
        int Y_Neighbour = direction.second;
        direction = this->getSearchable()->getLocationInSearchable(goalState);
        int X_Goal = direction.first;
        int Y_Goal = direction.second;
        neighbour->setHeuristic(abs(X_Goal - X_Neighbour) + abs(Y_Goal - Y_Neighbour));


    }

    /** updating the priority queue**/
    priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar>
    updatePriorityQueqe(priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> enteredQueqe) {
        priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> newQueqe;
        while (enteredQueqe.size() > 0) {
            newQueqe.push(enteredQueqe.top());
            enteredQueqe.pop();
        }
        return newQueqe;
    }

    /** clone **/
    Astar *copy() {
        return new Astar();
    }
};

#endif //EXX4_ASTAR_H
