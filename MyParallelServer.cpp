//
// Created by oem on 16/01/2020.
//
#define timeout_in_seconds 120

#include <netinet/in.h>
#include <thread>
#include <strings.h>
#include "MyParallelServer.h"

void MyParallelServer::start(int *sock, void *cli, socklen_t *clil, ClientHandler *client_handler) {
    //waiting until connection
    // accepting a client
    struct sockaddr cli1 = *((struct sockaddr *) clil);
    socklen_t clil1 = *clil;
    int sock1 = *sock;
    // time out of 2 minutes - if the program won't accept a client within 2 minutes it will closed
    struct timeval tv;
    tv.tv_usec = 0;
    tv.tv_sec = timeout_in_seconds;
    setsockopt(sock1, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

    while (true) {
        cout << "in start" << endl;
        int client_socket1 = accept(sock1, &cli1, &clil1);
        if (client_socket1 < 0) {
            cout << "NO CONNECTION TO CLIENT\n";
            exit(0);
        }
        // handle the client
        client_handler->handleClient(client_socket1);
        close(client_socket1);
        setsockopt(*sock, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
    }
}

int MyParallelServer::open(int port, ClientHandler *client_handler) {
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        //error
        cerr << "Bad connedction 2";
        exit(1);
    }
    struct sockaddr_in address, cli_addr;
    bzero((char *) &address, sizeof(address));
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    //sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    // calculating the number entered
    address.sin_port = htons((int) port);
    //we need to convert our number to a number that the network understands.
    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Bad connedction 3\n";
        exit(1);
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        cerr << "Bad connedction 4\n";
        exit(1);
    }

    socklen_t clilen = sizeof(cli_addr);
    int *sockfdPtr = &socketfd;
    struct sockaddr_in *client_addrPtr = &cli_addr;
    socklen_t *clientPtr = &clilen;

    std::thread t1(&MyParallelServer::start, this, sockfdPtr, client_addrPtr, clientPtr, client_handler);
    t1.join();
    cout << "in open" << endl;

    close(socketfd); //closing the listening socket
}