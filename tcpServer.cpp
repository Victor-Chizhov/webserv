#include "tcpServer.hpp"

tcpServer::tcpServer(int portno) {
    this->portno = portno;
}

tcpServer::~tcpServer() {
}

void tcpServer::closeSockets() {
    close(sockfd);
    close(newsockfd);
    exit(0);
}

void tcpServer::initSocketServer() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        err("ERROR: no port provided!", 1);
}

void tcpServer::err(std::string err, int codeErr) {
    std::cout << err.c_str() << std::endl;
    exit(codeErr);
}

void tcpServer::initSocketStruct() {
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(portno);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void tcpServer::bindSocket() {
    if(bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
        err("ERROR on binding!", 1);
    listen(sockfd, 5);
}

void tcpServer::initSocketClient() {
    lenClientAddr = sizeof(clientAddr);
    int newsockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &lenClientAddr);
    if(newsockfd < 0)
        err("ERROR on accept", 1);
    std::cout << "Server: got connection from " << inet_ntoa(clientAddr.sin_addr) << " port " << ntohs(clientAddr.sin_port) << std::endl;
    send(newsockfd, "Message was gotten!", 19, 0);

} 

void tcpServer::readMessage() {
    memset(message, 0, MAXSIZE);
    int n = read(newsockfd, message, MAXSIZE);
    if (n < 0) err("ERROR reading from socket", 1);
    
    printf("Here is the message: %s\n", message);
}

void tcpServer::runServer() {
    initSocketServer();
    initSocketStruct();
    bindSocket();
    initSocketClient();
    readMessage();
    closeSockets();
}




