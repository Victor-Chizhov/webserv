#include "../../include/ServerSocket.hpp"

ServerSocket::ServerSocket() {
    sockfd = -1;
    port = 0;
    backlog = 0;
    ip = "";
}

ServerSocket::~ServerSocket() {
    if (sockfd != -1) {
        close(sockfd);
    }
}

void ServerSocket::initListenSocket(unsigned long portno) {

    struct sockaddr_in servAddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        throw std::out_of_range("ERROR: openning socket!");
    memset(&servAddr, 0, sizeof(servAddr));

}



