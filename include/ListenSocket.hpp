#ifndef ListenSocket_HPP
#define ListenSocket_HPP

#include "Libraries.hpp"
#include "Server.hpp"

class Server;

class ListenSocket {
protected:
    struct sockaddr_in _addr;
    int _socket;
    std::vector<Server> _config;
    ListenSocket(){};
public:
    ListenSocket(std::string const &IP, int port, const std::vector<Server>& configs);
    virtual ~ListenSocket(){};

    void bindSocket();
    void listenSocket();
    void unlinkSocket();

    void checkSocket(int connection);

    const std::vector<Server> &getConfig() const;

    int getSocket() const { return _socket; };
    struct sockaddr_in getAddr() { return _addr; };
    void setSocket(int socket) { _socket = socket; };
    void setAddr(struct sockaddr_in addr) { _addr = addr; };

    ListenSocket(const ListenSocket &socket);
    ListenSocket &operator=(const ListenSocket &socket);
    bool operator==(const ListenSocket &socket) const;
};

#endif