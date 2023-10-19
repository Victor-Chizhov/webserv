#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXSIZE 1024

class tcpServer {

    private:
        int sockfd, newsockfd, portno;
        struct sockaddr_in servAddr, clientAddr;
        socklen_t lenClientAddr;
        char message[MAXSIZE];

        void initSocketServer();
        void initSocketStruct();
        void bindSocket();
        void initSocketClient();
        void readMessage();
        void closeSockets();


    public:
        tcpServer(int portno);
        ~tcpServer();

        void runServer();
        
        void err(std::string err, int codeErr);

};

#endif