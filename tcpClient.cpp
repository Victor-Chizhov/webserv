#include "tcpClient.hpp"

tcpClient::tcpClient(std::string address, int portno) {
    this->address = address;
    this->portno = portno;
}

tcpClient::~tcpClient() {
}

void tcpClient::err(std::string err, int code) {
    std::cout << err << std::endl;
    exit(code);
}

void tcpClient::initSocketClient() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        err("ERROR: openning socket!", 1);
}

void tcpClient::closeSocket() {
    close(sockfd);
}

void tcpClient::initSocketStruct() {
    memset(&servAddr, 0, sizeof(servAddr));
    
    if (inet_addr(address.c_str()) == -1) {
        struct hostent *server = gethostbyname(address.c_str());
        struct in_addr **tmp; 
        if(server == NULL)
            err("ERROR: Failed to resolve hostname!", 1);

        tmp = (struct in_addr **)server->h_addr_list;
            for (int i = 0; tmp[i] != NULL; ++i) {
                servAddr.sin_addr = *tmp[i];
                break;
        }
    } else {
        servAddr.sin_addr.s_addr = inet_addr(address.c_str());
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(portno);
}

void tcpClient::connectSocket() {
    if(connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
        err("ERROR connecting!", 1);

    std::cout << "Please enter the message: " << std::endl;
}

void tcpClient::


void tcpClient::runClient() {
    initSocketClient();
    initSocketStruct();
    connectSocket();
    sendMessage();
    closeSocket();
}