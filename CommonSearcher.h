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
    class MyComperator {
    public:
        bool operator()(State<T> *left, State<T> *right) {
            return (left->getTrailCost()) > right->getTrailCost();
        }
    };

protected:
    priority_queue<State<T> *, vector<State<T> *>, MyComperator> openPriority_queue;
    // Searchable<T> *searchable1;
    int evaluatedNodes = 0;
public:
    CommonSearcher() {}

    virtual solution search(Searchable<T> *searchable) = 0;


    //void setSearchable(Searchable<T>* searchableIN) {
    //   this->searchable1 = searchableIN;
    //}

    //Searchable<T>* getSearchable() {
    //   return this->searchable1;
    //};

    virtual ~CommonSearcher() {}

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

    string backTrace(State<T> *step) {
        cout << "trail cost is : ";
        cout << step->getTrailCost() << endl;
        // return the steps we did to get to this goal
        string solutionMatrix = "";
        State<T> *start = this->getSearchable()->getInitialeState();
        // checking if we arrived to the start state
        while (!step->Equals(start)) {
            State<T> *prev = step->getCameFRom();
            string s = getDirection(step, prev);
            solutionMatrix = s + solutionMatrix;
            solutionMatrix = "(" + to_string((int)step->getTrailCost()) + ")" + solutionMatrix;
            solutionMatrix = ", " + solutionMatrix;
            step = step->getCameFRom();
        }
        solutionMatrix = &solutionMatrix[2];
        cout << "number of nodes evaluated: ";
        cout << this->getNumberOfNodesEvaluated() << endl;
        return solutionMatrix;
    }

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
        } else if (yStep > yPrev) {
            return "Left";
        }
    }

};

#endif //EXX4_COMMONSEARCHER_H
