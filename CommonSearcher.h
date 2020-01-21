//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_COMMONSEARCHER_H
#define EXX4_COMMONSEARCHER_H

#include "Searcher.h"
#include "queue"
#include "unordered_set"

using namespace std;

template<class solution, class T>
class CommonSearcher : public Searcher<solution, T> {
public:
    CommonSearcher() {}

    virtual solution search(Searchable<T> *searchable) = 0;


    virtual ~CommonSearcher() {}

    /** returning the trace staring from the initial state until the goal state**/
    solution backTrace(State<T> *step) {
        cout << "***trail cost is : ";
        cout << step->getTrailCost() << endl;
        // return the steps we did to get to this goal
        string solutionMatrix = "";
        State<T> *start = this->getSearchable()->getInitialeState();
        // checking if we arrived to the start state
        while (!step->Equals(start)) {
            State<T> *prev = step->getCameFRom();
            string s = getDirection(step, prev);
            //if (s != "") {
                solutionMatrix = s + solutionMatrix;
                solutionMatrix = "(" + to_string((int) step->getTrailCost()) + ")" + solutionMatrix;
                solutionMatrix = ", " + solutionMatrix;
            //}
            step = step->getCameFRom();
        }
        solutionMatrix = &solutionMatrix[2];
        cout << "***number of nodes evaluated: ";
        cout << this->getNumberOfNodesEvaluated() << endl;
        return solutionMatrix;
    }

    /** return the direction we need to move from a step to another **/
    string getDirection(State<T> *step, State<T> *prev) {
        std::pair<int, int> stepDirection = this->getSearchable()->getLocationInSearchable(step);
        std::pair<int, int> prevDirection = this->getSearchable()->getLocationInSearchable(prev);

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
        } else if (yStep < yPrev) {
            return "Left";
        } else {
            // never reached
            return "";
        }
    }

};

#endif //EXX4_COMMONSEARCHER_H
