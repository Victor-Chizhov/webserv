#include "../../include/Server.hpp"

Server::Server() {
    this->hostName = "";
    this->port = 0;
    this->clientMaxBodySize = 0;
    this->serverName = "";
}

Server::~Server() {
}

void Server::setHostName(std::string hostName) {
    this->hostName = hostName;
}

void Server::setPort(int port) {
    this->port = port;
}

void Server::setClientMaxBodySize(unsigned long clientMaxBodySize) {
    this->clientMaxBodySize = clientMaxBodySize;
}

void Server::setServerName(std::string serverName) {
    this->serverName = serverName;
}

void Server::setErrorPages(std::map<int, std::string> errorPages) {
    this->errorPages = errorPages;
}

void Server::setLocation(std::vector<Location> location) {
    this->location = location;
}

std::string Server::getHostName() const {
    return this->hostName;
}

int Server::getPort() const {
    return this->port;
}

unsigned long Server::getClientMaxBodySize() const {
    return this->clientMaxBodySize;
}

std::string Server::getServerName() const {
    return this->serverName;
}

std::map<int, std::string> Server::getErrorPages() const {
    return this->errorPages;
}

std::vector<Location> Server::getLocation() const {
    return this->location;
}


