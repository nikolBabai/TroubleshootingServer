//
// Created by oem on 09/01/2020.
//

#ifndef EXX4_CLIENTHANDLER_H
#define EXX4_CLIENTHANDLER_H
class ClientHandler {
public:
    virtual void handleClient(int client_socket)= 0;
    virtual ClientHandler* copy()=0;
};
#endif //EXX4_CLIENTHANDLER_H
