//
// Created by oem on 09/01/2020.
//

#ifndef EXX4_SOLVER_H
#define EXX4_SOLVER_H

#include "string"

using namespace std;

template<class problem, class solution>
class Solver {
public:
    virtual solution solve(problem pb) = 0;

    virtual Solver *copy() = 0;

    virtual ~Solver() = default;
};

#endif //EXX4_SOLVER_H
