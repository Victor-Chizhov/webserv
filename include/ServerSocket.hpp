#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include "EventManager.hpp"
#include "Libraries.hpp"

class EventManager;


class ServerSocket {
public:
    ServerSocket();
    ~ServerSocket();
    void initListenSocket(std::string ipAddress, int port);
    void stop();
    int getListenSocket() const;

private:
    int listenSocket;
    int backlog;
    struct sockaddr_in serverAddr;
};


#endif