//
// Created by oem on 09/01/2020.
//

#ifndef EXX4_CACHEMANAGER_H
#define EXX4_CACHEMANAGER_H

#include "string"
using namespace std;
template<class problem, class solution>

class CacheManager {
public:
    virtual bool isSolutionExist(problem p) = 0;

    virtual solution getSolution(problem p) = 0;

    virtual void saveSolution(problem p, solution *s) = 0;

    virtual CacheManager* copy() = 0;
};
#endif //EXX4_CACHEMANAGER_H
