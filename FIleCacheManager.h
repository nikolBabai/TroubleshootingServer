//
// Created by oem on 09/01/2020.
//

#ifndef EXX4_FILECACHEMANAGER_H
#define EXX4_FILECACHEMANAGER_H

#include <stdio.h>
#include "string"
#include "iostream"
#include <unordered_map>
#include <fstream>
#include "CacheManager.h"
#include<functional>
#include "vector"

using namespace std;

template<class solution>
class FileCacheManager : public CacheManager<string, solution> {
private:
    int capacity;
    int totalItemsInCache;
    vector<string> problems;
public:

    FileCacheManager(int capacityIn) {
        this->capacity = capacityIn;
        this->totalItemsInCache = 0;
    }

    /**saving the solution in a file **/
    void saveToFile(string key, solution *obj) {
        ofstream file_obj;
        std::hash<std::string> hasher;
        long hashed = hasher(key);
        string hashString = to_string(hashed);
        // Opening file in append mode
        std::ofstream out(hashString + ".txt");
        out << *obj << endl;
        out.close();
    }

    /** saving a solution by inserting to the map and saving the solution in a file**/
    void saveSolution(string key, solution *obj) {
        insert(key, *obj);
    }

    /** returning a solution that was found in a file**/
    solution *readFromFile(string key) {
        string STRING;
        ifstream file_obj;
        file_obj.open(key);
        while ((file_obj.peek() != EOF)) {
            getline(file_obj, STRING);
        }
        file_obj.close();
        return new string(STRING);
    }

    /**insert to the map**/
    void insert(string key, solution obj) {
        this->problems.push_back(key);
        this->totalItemsInCache++;
        saveToFile(key, &obj);

    }

    /** searching a solution in the files**/
    bool isSolutionExist(string key) {
        std::hash<std::string> hasher;
        long hashed = hasher(key);
        string hashString = to_string(hashed);
        hashString += ".txt";
        return fexists(hashString);
    }

    /** returning a solution in the files**/
    solution getSolution(string key) {
        //type* objIn;// = new type()
        solution t;
        std::hash<std::string> hasher;
        long hashed = hasher(key);
        string hashString = to_string(hashed);
        if (fopen((hashString + ".txt").c_str(), "r")) {
            hashString += ".txt";
            solution *objIn = readFromFile(hashString);
            return *objIn;
        } else {
            return nullptr;
        }
    }

    virtual ~FileCacheManager() {

    }

    bool dataContaines(vector<string> data, string s) {
        for (auto n: data) {
            if (n == s) {
                return true;
            }
        }
        return false;
    }

    /** searching a solution in the files**/
    bool fexists(const std::string &filename) {
        std::ifstream ifile(filename.c_str());
        return (bool) ifile;
    }

    /** clone **/
    FileCacheManager *copy() {
        return new FileCacheManager(0);
    }
};

#endif //EXX4_FILECACHEMANAGER_H
