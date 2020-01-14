//
// Created by oem on 09/01/2020.
//

#ifndef EXX4_STRINGREVERSER_H
#define EXX4_STRINGREVERSER_H

#include "string"
#include "Solver.h"
using namespace std;
template<class problem, class solution>
class StringReverser : public Solver<string , string> {
public:
    string solve(string  s);

    string reverseStr(string str);
};


#endif //EXX4_STRINGREVERSER_H
