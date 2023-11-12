#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Libraries.hpp"
#include "Client.hpp"
#include "../src/request/Response.hpp"

class Client;


class EventManager {
public:
    EventManager();
    ~EventManager();

    void addServerSocket(int clientSocket);
	void CreateAddClientSocket(int serverSocket);

    void waitAndHandleEvents();

private:
    fd_set readSet;
	fd_set writeSet;
	fd_set read_master;
	fd_set write_master;
    std::vector<int> serverSockets;
	std::list<Client *> clientSockets;
    int maxSocket;
	Response responder;
};



#endif