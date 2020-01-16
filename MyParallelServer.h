//
// Created by oem on 16/01/2020.
//

#ifndef EXX4_MYPARALLELSERVER_H
#define EXX4_MYPARALLELSERVER_H

#include "Server.h"
class MyParallelServer : public server_side::Server {

    int open(int port, ClientHandler *client_handler);

    void start(int *sock, void *cli, socklen_t *clil, ClientHandler *client_handler);
};


#endif //EXX4_MYPARALLELSERVER_H
