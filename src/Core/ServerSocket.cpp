#include "../../include/ServerSocket.hpp"

ServerSocket::ServerSocket() : listenSocket(-1), backlog(120) {

}

ServerSocket::~ServerSocket() {
}

void ServerSocket::stop() {
	if (close(listenSocket) == -1) {
        perror("Error closing socket");
    }
}

int ServerSocket::getListenSocket() const {
    return listenSocket;
}

void ServerSocket::initListenSocket(std::string ipAddress, int port) {
//    std::cout << "ipAddress: " << ipAddress << " | port: " << port << std::endl;
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
//    std::cout << listenSocket << std::endl;
    if (listenSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;

    if (inet_pton(AF_INET, ipAddress.c_str(), &(serverAddr.sin_addr)) <= 0) {
        perror("Error of ip number");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_port = htons(port);

    int opt = 1;
    setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding socket");
        close(listenSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(listenSocket, backlog) == -1) {
        perror("Error listening on socket");
        close(listenSocket);
        exit(EXIT_FAILURE);
    }
}
