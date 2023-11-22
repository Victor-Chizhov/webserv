#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include "EventManager.hpp"
#include "Libraries.hpp"
#include "Config.hpp"

class EventManager;



class ServerSocket {
public:
    ServerSocket();
    ~ServerSocket();
    void start();
    void configure(int port, int backlog);
    void stop();
    void createListenSockets();

private:
    int listenSocket;
    int port;
    int backlog;
	EventManager eventManager;

};


#endif