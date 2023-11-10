#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

#include "EventManager.hpp"

class EventManager;


//Этот класс ответственен за создание и управление слушающим сокетом, а также обработку входящих соединений.

class ServerSocket {
public:
    ServerSocket();
    ~ServerSocket();
    void start();
    void configure(int port, int backlog);
    void stop();

private:
    int listenSocket;
    int port;
    int backlog;
	EventManager eventManager;
	
    // Другие члены данных для настроек сервера
};


#endif