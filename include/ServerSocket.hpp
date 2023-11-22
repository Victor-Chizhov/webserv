#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include "EventManager.hpp"
#include "Libraries.hpp"

class EventManager;



class ServerSocket {
public:
    ServerSocket();
    ~ServerSocket();

    void initListenSocket(unsigned long portno);

private:
    int sockfd;
    int port;
    std::string ip;
    int backlog;
	EventManager eventManager;

};


#endif