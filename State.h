//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_STATE_H
#define EXX4_STATE_H

#include "string"

using namespace std;

/** holds information about the components in the searchable class**/
template<class T>
class State {
private:
    T state;
    double cost;
    double trailCost = 0;
    State<T> *cameFrom;
    double heuristic;
public:
    bool Equals(State<T> *s) {
        return state == s->getState();
    }

    State(T state, double costIn, double costTrailIn) : state(state), cost(costIn), trailCost(costTrailIn) {
    }

    T getLocationT() {
        return state;
    };

    void setCost(double costIn) {
        this->cost = costIn;
    }

    void setTrailCost(double costIn) {
        this->trailCost = costIn;
    }

    double getCost() {
        return this->cost;
    }

    double getTrailCost() {
        return this->trailCost;
    }

    void setCameFRom(State<T> *cameFromIn) {
        this->cameFrom = cameFromIn;
    }

    State<T> *getCameFRom() {
        return this->cameFrom;
    }

    T getState() {
        return this->state;
    }

    double getHeuristic() {
        return this->heuristic;
    }

    void setHeuristic(double heuristic) {
        this->heuristic = heuristic;
    }
};

#endif //EXX4_STATE_H
