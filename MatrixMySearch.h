//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_MATRIXMYSEARCH_H
#define EXX4_MATRIXMYSEARCH_H

#include "Searchable.h"
#include "deque"
#include "Point.h"
#include <queue>
class MatrixMySearch : public Searchable<Point> {
private:
    State<Point> *startState;
    State<Point> *goalState;
    Point* start;
    Point* destination;
     int rows;
     int columns;
    State<Point> ***matrixOfStates;
    deque<string> dequeStrings;
public:
    MatrixMySearch(const int rowsIn,const int columnsIn, deque<string> dequeStrings);

    State<Point>* getInitialeState() override;

    State<Point>* getGoalState() override;

    list<State<Point>*> createSuccessors(State<Point>* s) override;

    void initializeMatrix();

    string edit(string s);

    double getCostInMatrix(int row, int col);

    bool isGoal(State<Point> *s);

    int *editcomma(string line);

    void initializeStates();

    std::pair<int, int> getLocationInSearchable(State<Point> *state) override;
};

#endif //EXX4_MATRIXMYSEARCH_H
