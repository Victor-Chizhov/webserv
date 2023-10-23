#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXSIZE 4096

class tcpServer {

    private:


    public:
        void runServer();

};

#endif