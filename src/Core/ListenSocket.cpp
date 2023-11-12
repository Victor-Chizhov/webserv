#include "../../include/ListenSocket.hpp"

ListenSocket::ListenSocket(std::string const &IP, int port, const std::vector<Server>& configs) {
    _config = configs;
    in_addr_t addr = inet_addr(IP.c_str());
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = addr;
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    checkSocket(_socket);
    int opt = 1;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0) {
        perror("setsockopt failed to set SO_REUSEADDR flag for socket in ServerSocket constructor (ServerSocket.cpp)");
        exit(1);
    }
    fcntl(_socket, F_SETFL, O_NONBLOCK);
    bindSocket();
    listenSocket();
}

void ListenSocket::checkSocket(int connection) {
    if (connection < 0) {
        perror("socket failed to connect. fix config file (ServerSocket.cpp)");
        exit(1);
    }
}

void ListenSocket::bindSocket() {
    checkSocket(bind(_socket, (struct sockaddr *) &_addr, sizeof(_addr)));
}

void ListenSocket::listenSocket() {
    checkSocket(listen(_socket, SOMAXCONN));
}

const std::vector<Server> &ListenSocket::getConfig() const {
    return _config;
}

ListenSocket::ListenSocket(const ListenSocket &socket) {
    *this = socket;

}

ListenSocket &ListenSocket::operator=(const ListenSocket &socket) {
    if (this != &socket) {
        _addr = socket._addr;
        _socket = socket._socket;
        _config = socket._config;
    }
    return *this;
}

bool ListenSocket::operator==(const ListenSocket &socket) const {
    return _socket == socket._socket;
}