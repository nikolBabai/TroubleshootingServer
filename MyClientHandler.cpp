//
// Created by oem on 09/01/2020.
//
#include <unistd.h>
#include "MyClientHandler.h"
#include "Searchable.h"
#include "MatrixMySearch.h"

using namespace std;

MyClientHandler::MyClientHandler(Solver<Searchable<Point>, string> *solver,
                                 CacheManager<string, string> *cm) : solver(solver), cm(cm) {}

void MyClientHandler::handleClient(int client_socket) {
    string line;
    char buffer[1024] = {0};
    while (true) {
        line = "";
        int valread = ::read(client_socket, buffer, 1024);
        line = buffer;
        if (line.find("end") != std::string::npos) {
            break;
        }
        if (valread < 1024) {
            // we have all the line
            dequeStrings.push_back(line);
        } else {
            while ((valread >= 1024)) {
                valread = ::read(client_socket, buffer, 1024);
                line += buffer;
            }
            dequeStrings.push_back(line);
        }
    }
    // building the problem - the matrix
    buildProblem();
    /**
    // checking if the problem has a solution in the cashManeger
    if (this->cm->isSolutionExist(line)) {
        // there is a solution - returning it to the client
        std::cout << "there is a solution" << endl;
        std::cout << cm->getSolution(line) << endl;
        string solution = cm->getSolution(line);
        //::write(client_socket, solution, sizeof(solution));
    } else {
        // there is'nt a solution - solving the problem, saving it in the cache
        string solution1 = solver->solve(line);
        cm->saveSolution(line, &solution1);
        std::cout << "there is'nt a solution" << endl;
        // returning to the client the solution
        //::write(client_socket, solution1);
    }
     **/
}

//read line by line
//when getthing to last two lines get the point x,y of the first
//create searchable matrix
//call matrix constructor with start point end point
void MyClientHandler::buildProblem() {
    // minus 2 because we also have the start and end in the deque
    int rows = this->dequeStrings.size() - 2;
    int cols = 1;
    // receiving a line of a row from the deque
    string line = this->dequeStrings.front();
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',') {
            cols += 1;
        }
    }
    // building a matrix
    buildMatrix(rows, cols);
}

string MyClientHandler::edit(string s) {
    size_t prev = 0, pos;
    while ((pos = s.find_first_of(" ", prev)) != std::string::npos) {
        string cut1 = s.substr(prev, pos);
        string cut2 = s.substr(pos + 1, s.length());
        s = cut1 + cut2;
    }
    return s;
}

void MyClientHandler::buildMatrix(int rows, int cols) {
    //Point *start, Point *destination, int rows, int columns, deque<string> dequeStrings);
    const int r = rows;
    const int c = cols;
    this->matrix = new MatrixMySearch(r, c, this->dequeStrings);
}
