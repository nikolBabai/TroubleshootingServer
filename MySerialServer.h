//
// Created by oem on 09/01/2020.
//

#ifndef EXX4_MYSERIALSERVER_H
#define EXX4_MYSERIALSERVER_H


#include "Server.h"

class MySerialServer : public server_side::Server {
public:
    int open(int port, ClientHandler *client_handler);

    int close(int port);

    void start(int* sock,void* cli, socklen_t * clil ,ClientHandler* client_handler);
    };


#endif //EXX4_MYSERIALSERVER_H
