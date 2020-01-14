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
using namespace std;

template<class problem = string>
class node {
public:
    string key;
    problem *obj;
    node<problem> *prev;
    node<problem> *next;

    node(string keyIn, problem *objIn) {
        this->key = keyIn;
        this->obj = objIn;
    }

    virtual ~node() {
      //  delete(obj);
        /**to check**/
    }

    node() {
    }
};

template<class solution>
class FileCacheManager : public CacheManager<string ,solution> {
private:
    int capacity;
    int totalItemsInCache;
    node<string> *head;
    node<string> *tail;
    unordered_map<string, node<string> *> mp;
public:

    FileCacheManager(int capacityIn) {
        this->capacity = capacityIn;
        this->totalItemsInCache = 0;
        head = new node<string>();
        tail = new node<string>();
        head->key = "HEAD";
        tail->key = "TAIL";
        // Wire the head and tail together
        head->next = tail;
        tail->prev = head;
        mp.insert({"HEAD", (head)});
        mp.insert({"TAIL", (tail)});
    }

    void saveToFile (string key, solution *obj) {
        cout<<"test save to file:";
        cout<<*obj<<endl;
        ofstream file_obj;
        std::hash<std::string>hasher;
        long hashed= hasher(key);
        string hashString= to_string(hashed);
        // Opening file in append mode
        file_obj.open(hashString + ".txt");
        file_obj.write((char *) obj, sizeof(solution));
        file_obj.close();
    }


    void saveSolution(string key, solution *obj) {
        insert(key, obj);
    }
    solution *readFromFile(string key) {
        ifstream file_obj;
        solution *objPtr = new solution();
        // Opening file in input mode
        //string s = key;
        //std::hash<std::string>hasher;
        //long hashed= hasher(key);
        //string hashString= to_string(hashed);
        file_obj.open(key);
        file_obj.read((char *) objPtr, sizeof(solution));
        file_obj.close();
        return objPtr;
    }

    // insert to the map
    void insert(string key, string obj) {
        string *objIn = new string(obj);
        string s= *objIn;
        insert(key, objIn);
    }

    void insert(string key, string *objIn) {
        saveToFile(key, objIn);
        //node <type*> nodeIn= new ::node<type>(key,new type(obj));
        node<string> *nodeIn = new ::node<string>(key, objIn);
        auto search = this->mp.find(key);//o(1)
        if (search != this->mp.end()) {
            node<string> *temp = (search->second);
            ((search->second)->obj) = objIn;
            moveToHead(nodeIn, temp);
            return;
        }
        addToFront(nodeIn);
        put(key, nodeIn);
    }
    void addToFront(node<string> *nodeIn) {
/*
         // Wire up the new node being to be inserted
        if (this->capacity != this->totalItemsInCache) {
            nodeIn->prev = head;
            nodeIn->next = head->next;
            auto search = this->mp.find(nodeIn->key);
            if (search != this->mp.end()) {
                (search->second)->prev = head;
                (search->second)->next = head->next;
            }
            node<string> *temp = head->next;
            (head->next)->prev = nodeIn;
            head->next = nodeIn;
            search = this->mp.find((temp)->key);
            if (search != this->mp.end()) {
                (search->second)->prev = nodeIn;
            }
            search = this->mp.find(head->key);
            if (search != this->mp.end()) {
                (search->second)->next = nodeIn;
            }
            this->totalItemsInCache++;
        } else {
            node<string> *temp = tail->prev;
            removeFromList(temp);
            mp.erase(temp->key);
            delete temp;
            addToFront(nodeIn);
        }
 */
        // Wire up the new node being to be inserted
            nodeIn->prev = head;
            nodeIn->next = head->next;
            auto search = this->mp.find(nodeIn->key);
            if (search != this->mp.end()) {
                (search->second)->prev = head;
                (search->second)->next = head->next;
            }
            node<string> *temp = head->next;
            (head->next)->prev = nodeIn;
            head->next = nodeIn;
            search = this->mp.find((temp)->key);
            if (search != this->mp.end()) {
                (search->second)->prev = nodeIn;
            }
            search = this->mp.find(head->key);
            if (search != this->mp.end()) {
                (search->second)->next = nodeIn;
            }
            this->totalItemsInCache++;
    }

    // removing from the map
    void removeFromList(node<string> *nodeIn) {
        node<string> *savedPrev = nodeIn->prev;
        node<string> *savedNext = nodeIn->next;
        savedPrev->next = savedNext;
        savedNext->prev = savedPrev;
        auto search = this->mp.find(savedPrev->key);
        if (search != this->mp.end()) {
            (search->second)->next = savedNext;
        }
        search = this->mp.find(savedNext->key);
        if (search != this->mp.end()) {
            (search->second)->prev = savedPrev;
        }
        --this->totalItemsInCache;
    }

    void moveToHead(node<string> *nodeIn, node<string> *temp) {
        removeFromList(temp);
        addToFront(nodeIn);
    }

    bool isSolutionExist(string key) {
        auto search = mp.find(key);
        if (search == mp.end()) {
            return false;
        }
        return true;
    }
   // bool isSolutionExist(string key) {
    //}

    solution getSolution(string key) {
        //type* objIn;// = new type()
        solution t;
        auto search = mp.find(key);
        if (search != mp.end()) {
            std::hash<std::string>hasher;
            long hashed= hasher(key);
            string hashString= to_string(hashed);
            if (fopen((hashString + ".txt").c_str(), "r")) {
                hashString += ".txt";
                solution *objIn = readFromFile(hashString);
                //insert(key, objIn);
                return *objIn;
            }
            throw "key not exists both in cache and disk!"; // we should throw an exception here, but for Leetcode's sake
        }
        //check
        moveToHead((search->second), (search->second));
        return *(((search->second)->obj));
    }

    template<typename Func>
    void foreach(Func f) {
        node<string> *tmp;
        tmp = head->next;
        while (tmp != this->tail) {
            f(*(tmp->obj));
            tmp = tmp->next;
        }
    }

    void put(string keyIn, node<string> *node1) {
        mp[keyIn] = node1;
        // If over capacity remove the LRU item
    }

    virtual ~FileCacheManager() {
        node<string> *headIn = head;
        while (headIn->next) {
            node<string> *temp = headIn->next;
            delete (headIn);
            headIn = temp;
        }
        delete (tail);
    }
};

#endif //EXX4_FILECACHEMANAGER_H
