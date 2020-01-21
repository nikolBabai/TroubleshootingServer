//
// Created by oem on 16/01/2020.
//

#ifndef EXX4_MYPARALLELSERVER_H
#define EXX4_MYPARALLELSERVER_H

#include "Server.h"
#include <stack>
#include <unistd.h>
class MyParallelServer : public server_side::Server {
private:


   stack<pthread_t> thread_List;
public:
    struct Info {
        int sockfd;
        ClientHandler *Client_Handler;
    };

    MyParallelServer() {}

    int open(int port, ClientHandler *client_handler);

    void start(int *sock, socklen_t *clil, ClientHandler *client_handler);

    virtual ~MyParallelServer() {}

    int getSocket();

    int stop(int);

    static void *StarttheThreadClient(void *infoIn);
};


#endif //EXX4_MYPARALLELSERVER_H
