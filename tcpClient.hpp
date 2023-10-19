#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define MAXSIZE 4096


class tcpClient {

    private:
        int sockfd, portno;
        struct sockaddr_in servAddr;
        std::string address;
        char message[MAXSIZE];

        void initSocketClient();
        void initSocketStruct();
        void connectSocket();
        void closeSocket();
        void sendMessage();


    public:
        tcpClient(std::string address, int portno);
        ~tcpClient();
        void err(std::string err, int code);
        void runClient();
        
};

#endif