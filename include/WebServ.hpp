#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "Libraries.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "ListenSocket.hpp"
#include "EventManager.hpp"

class ListenSocket;
class EventManager;
class Client;
class Server;

class WebServ {
private:
    EventManager *_eventManager;
    std::vector<ListenSocket> _listenSockets;
    std::list<Client> _clients;
    std::vector<Server> _servers; //зачем нужен вектор сервер конфигов?
public:
    WebServ();
    ~WebServ(){};
    void parseConfigFile(const std::string &configFile);
    void start();
    const std::vector<Server> &getServers() const;
    void addListenSocketsToEventManager();
    void generateListenSockets();
    ListenSocket &getListenSocketBySocketFd(int socket);
    std::vector<Server> getServersByHostAndPort(std::string host, int port);
};

#endif