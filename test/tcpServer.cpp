#include "tcpServer.hpp"

void err(std::string err, int code) {
    std::cout << err.c_str() << std::endl;
    exit(code);
}


void tcpServer::runServer() {
   int sockfd, portno;             

    struct sockaddr_in servAddr, clientAddr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        err("ERROR: openning socket!", 1);
    memset(&servAddr, 0, sizeof(servAddr));

    portno = 11111;


    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(portno);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

     std::cout << "Server: got connection from " << inet_ntoa(servAddr.sin_addr) << " port " << ntohs(servAddr.sin_port) << std::endl;

    if(bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
        err("ERROR on binding!", 1);

    listen(sockfd, 5);

    socklen_t lenClientAddr = sizeof(clientAddr);

    int newsockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &lenClientAddr);
    if(newsockfd < 0)
        err("ERROR on accept", 1);

    std::cout << "Server: got connection from " << inet_ntoa(clientAddr.sin_addr) << " port " << ntohs(clientAddr.sin_port) << std::endl;

    send(newsockfd, "Message was gotten!", 19, 0);

    char message[MAXSIZE];
    memset(message, 0, MAXSIZE);

    int n = read(newsockfd, message, MAXSIZE);
    if (n < 0) err("ERROR reading from socket", 1);
    printf("Here is the message: %s\n", message);
    
    close(newsockfd);
    close(sockfd);
}




