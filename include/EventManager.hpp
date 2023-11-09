#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <vector>
#include <list>
#include <sys/select.h>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

#include "Client.hpp"

class Client;

//Класс, отвечающий за управление событиями. 

class EventManager {
public:
    EventManager();
    ~EventManager();

    // Метод для добавления клиентского сокета в event-менеджер
    void addServerSocket(int clientSocket);
	void addClientSocket(int clientSocket);

    // Метод для ожидания событий и их обработки
    void waitAndHandleEvents();

private:
    fd_set readSet;
    std::vector<int> serverSockets;
	std::list<Client> clientSockets;
    int maxSocket;
};



#endif