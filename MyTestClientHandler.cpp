//
// Created by oem on 09/01/2020.
//

//#include <unistd.h>
#include <unistd.h>
#include <sys/socket.h>
#include "iostream"
#include "MyTestClientHandler.h"

using namespace std;

MyTestClientHandler::MyTestClientHandler(Solver<string, string> *solverIn,
                                         CacheManager<string, string> *cashIn) {
    this->solver = solverIn;
    this->cm = cashIn;
}

void MyTestClientHandler::handleClient(int client_socket) {
        std::size_t sizeLine = 0;
        string line = "";
        char buffer[1024] = {0};
        int flag = 1;
        while (flag) {
            int valread = ::read(client_socket, buffer, 1024);
            line = buffer;
            if (valread < 1024) {
                // we have all the line
                flag = 0;
            }
            sizeLine += valread;
        }
        // checking if the problem has a solution in the cashManeger
        if (this->cm->isSolutionExist(line)) {
            // there is a solution - returning it to the client
            std::cout << "there is a solution" << endl;
            string sol = cm->getSolution(line);
            std::cout << sol << endl;
            char const *solution = (sol).c_str();
            send(client_socket, solution, sizeLine, 0);
        } else {
            // there is'nt a solution - solving the problem, saving it in the cache
            string solution1 = solver->solve(line);
            cm->saveSolution(line, &solution1);
            std::cout << "there is'nt a solution" << endl;
            // returning to the client the solution
            char const *solutionChar = (solution1).c_str();
            int is_sent = send(client_socket, solutionChar, sizeLine, 0);
            if (is_sent == -1) {
                std::cout<<"Error sending message reveres"<<std::endl;
            } else {
                std::cout<<"solution  message sent to server" <<std::endl;
            }
    }
}
