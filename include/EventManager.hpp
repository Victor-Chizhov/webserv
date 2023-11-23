#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Libraries.hpp"
#include "Client.hpp"
#include "../src/request/Response.hpp"
#include "../include/ServerSocket.hpp"

class Client;
class ServerSocket;


class EventManager {
public:
    EventManager();
    ~EventManager();

    void addServerSocket(ServerSocket &serverSocket);
	void CreateAddClientSocket(int serverSocket);

    void waitAndHandleEvents();

private:
    fd_set readSet;
	fd_set writeSet;
	fd_set read_master;
	fd_set write_master;
    std::vector<ServerSocket> serverSockets;
	std::list<Client *> clientSockets;
    int maxSocket;
};



#endif