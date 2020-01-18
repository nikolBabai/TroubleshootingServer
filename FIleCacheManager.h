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
class FileCacheManager : public CacheManager<string ,solution> {
private:
    int capacity;
    int totalItemsInCache;
    vector<string> problems;
public:

    FileCacheManager(int capacityIn) {
        this->capacity = capacityIn;
        this->totalItemsInCache = 0;
    }

    void saveToFile (string key, solution *obj) {
        //cout<<"test save to file:";
        //cout<<*obj<<endl;
        ofstream file_obj;
        std::hash<std::string>hasher;
        long hashed= hasher(key);
        string hashString= to_string(hashed);
        // Opening file in append mode
        std::ofstream out(hashString + ".txt");
        out<<*obj<<endl;
        out.close();
    }


    void saveSolution(string key, solution *obj) {
       // solution s = *obj;
       // cout<<"the solution was saved "+s<<endl;
        insert(key, *obj);
    }
    solution *readFromFile(string key) {
        string STRING;
        ifstream file_obj;
        file_obj.open(key);
        while(( file_obj.peek() != EOF )){
            getline(file_obj,STRING);
           // cout<<STRING;
        }
        file_obj.close();
        //std::cout<<"here"<<endl;
        return new string (STRING);
    }

    // insert to the map
    void insert(string key, solution obj) {
        this->problems.push_back(key);
        this->totalItemsInCache++;
        saveToFile(key, &obj);

    }
    bool isSolutionExist(string key) {
        std::hash<std::string>hasher;
        long hashed= hasher(key);
        string hashString= to_string(hashed);
            hashString += ".txt";
        return  fexists(hashString);
        /*
        return dataContaines(this->problems, key);
         */
    }
    solution getSolution(string key) {
        //type* objIn;// = new type()
        solution t;
            std::hash<std::string>hasher;
            long hashed= hasher(key);
            string hashString= to_string(hashed);
            if (fopen((hashString + ".txt").c_str(), "r")) {
                hashString += ".txt";
                solution *objIn = readFromFile(hashString);
                return *objIn;
            throw "key not exists both in cache and disk!"; // we should throw an exception here, but for Leetcode's sake
        }
    }
    virtual ~FileCacheManager() {

    }

    bool dataContaines(vector<string> data, string s) {
        for (auto n: data) {
            if (n==s) {
                return true;
            }
        }
        return false;
    }
    bool fexists(const std::string& filename) {
        std::ifstream ifile(filename.c_str());
        return (bool)ifile;
    }
   FileCacheManager* copy (){
        return new FileCacheManager(0);
    }
};

#endif //EXX4_FILECACHEMANAGER_H
