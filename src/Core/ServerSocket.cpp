#include "../../include/ServerSocket.hpp"

ServerSocket::ServerSocket() : listenSocket(-1), port(0), backlog(0) {

}

ServerSocket::~ServerSocket() {
    if (listenSocket != -1) {
        close(listenSocket);
    }
}

void ServerSocket::createListenSockets() {
    for (int i = 0; i < servers.size(); i++) {

    }
}

void ServerSocket::start() {
    createListenSockets();

}
