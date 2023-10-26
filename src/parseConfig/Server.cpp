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

std::string Server::getIpAddress() const {
    return this->ipAddress;
}

void Server::setServerConfig(std::string serverConfig) {
    this->serverConfig.push_back(serverConfig);
}

void Server::setIpAddress(std::string ipAddress) {
    this->ipAddress = ipAddress;
}

void Server::printServerConfig() const {
    for (std::vector<std::string>::const_iterator it = this->serverConfig.begin(); it != this->serverConfig.end(); it++) {
        std::cout << *it << std::endl;
    }
}

void Server::addAttributesInServer() {
    for (size_t i = 0; i < serverConfig.size(); i++) {
        cutDataStr(serverConfig[i], "listen", ipAddress);
        cutDataStr(serverConfig[i], "server_name", serverName);
        cutDataStr(serverConfig[i], "host_name", hostName);
        cutDataNum(serverConfig[i], "port", port);
        cutDataNum(serverConfig[i], "client_max_body_size", clientMaxBodySize);
        cutDataMap(serverConfig[i], "error_page", errorPages);
    }
    std::cout << ipAddress << std::endl;
    std::cout << serverName << std::endl;
}


