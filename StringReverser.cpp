//
// Created by oem on 09/01/2020.
//

#include <iostream>
#include "StringReverser.h"
using namespace std;
template<>
string StringReverser<string , string>::solve(string s) {
    string *copy = new string;
    *copy= s;
    std::cout << *copy<< endl;
    int n = s.length();
    // Swap character starting from two
    // corners
    for (int i = 0; i < n / 2; i++) {
        swap((*copy)[i], (*copy)[n - i - 1]);
    }
    std::cout << *copy<< endl;
    return *copy;
}