//
// Created by oem on 09/01/2020.
//

#ifndef EXX4_SERVER_H
#define EXX4_SERVER_H

#include <cstdlib>
#include <netinet/in.h>
#include "string"
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "FIleCacheManager.h"
//#include "MySerialServer.h"

using namespace std;
namespace server_side {
    // An interface in a namespace
    class Server {
    private:
        int socketNum;
        int port;
    public:
        // pure virtual function
        virtual int open(int port, ClientHandler *client_handler) = 0;

        virtual int close(int port) = 0;

    };
}
#endif //EXX4_SERVER_H
