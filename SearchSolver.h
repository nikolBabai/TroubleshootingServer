//
// Created by oem on 11/01/2020.
//

#ifndef EXX4_SEARCHSOLVER_H
#define EXX4_SEARCHSOLVER_H

#include "Solver.h"
#include "Searcher.h"

/** this class implements the solver interface by getting a searcher and solving a problem from type searchable**/
template<class problem, class solution, class T>
class SearchSolver : public Solver<problem, solution> {
private:
    Searcher<solution, T> *searcher;
public:
    solution solve(problem pb) {
        return searcher->search(pb);
    }

    SearchSolver(Searcher<solution, T> *searcher) : searcher(searcher) {}

    SearchSolver(const SearchSolver &obj) {
        searcher = obj.searcher.copy();
    }

    Searcher<solution, T> *getSearcher() {
        return this->searcher;
    }

    /** clone **/
    SearchSolver *copy() {
        return new SearchSolver(searcher->copy());
    }

};


#endif //EXX4_SEARCHSOLVER_H
