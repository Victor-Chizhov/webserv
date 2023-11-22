#include "../../include/WebServer.hpp"

WebServer::WebServer(std::string pathConfig) {
    this->pathConfig = pathConfig;
    this->configLines = std::vector<std::string>();
    this->servers = std::vector<Server>();
}


bool WebServer::removeComments(std::string &line) {
    std::string::size_type pos = line.find('#');
    if (pos != std::string::npos) {
        line.erase(pos);
    }
    return true;
}

void WebServer::saveConfigInConfigLine() {
    std::ifstream inputFile(this->pathConfig);
    if (!inputFile.is_open()) {
        throw std::out_of_range("Error: could not open file");
    }
    std::string line;
    while(getline(inputFile, line)) {
        removeComments(line);
        if (line.empty()) { continue; }
        configLines.push_back(line);
    }
    inputFile.close();
}


void WebServer::createVectorOfServers() {
    addConfigInArray<Server>(servers, configLines, "server");
}

void WebServer::fillEachServerWithData() {
    for (size_t i = 0; i < servers.size(); i++) {
        servers[i].addDataInServer();
    }
}

void WebServer::addConfigData() {
    createVectorOfServers();
    fillEachServerWithData();
}

void WebServer::parseConfig() {
    saveConfigInConfigLine();
    addConfigData();
}

int WebServer::countPorts() {
    for (size_t i = 0; i < servers.size(); i++) {
        int port = servers[i].getPort();
        ports.insert(port);
    }
    return ports.size();
}

void WebServer::createStructServerSocket() {
    for (size_t i = 0; i < servers.size(); i++) {
        int port = servers[i].getPort();
        std::string ip = servers[i].getIp();

        serverSockets[i].initListenSocket(port, ip, backlog);
    }
}


void WebServer::runListenSocket() {
    int size = countPorts();
    serverSockets.resize(size);
    for (int i = 0; i < size; i++) {

    }


}


void WebServer::start() {
    runListenSocket();
}