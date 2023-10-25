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

void Server::cutString() {

}

void Server::addAttributesInServer() {
    for (size_t i = 0; i < serverConfig.size(); i++) {
        if (serverConfig[i].find("listen") != std::string::npos) {
            std::string ip = serverConfig[i].substr(serverConfig[i].find(" ") + 1);
            this->setIpAddress(ipAddress.c_str());
        }

    }
}


