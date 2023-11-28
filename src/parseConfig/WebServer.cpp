#include "../../include/WebServer.hpp"

WebServer::WebServer(std::string pathConfig) {
    this->pathConfig = pathConfig;
    this->configLines = std::vector<std::string>();
    this->servers = std::vector<Server>();
    eventManager = new EventManager();
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

void WebServer::addDataInCurrentPath() {
    char currentPath[PATH_MAX];
    if (getcwd(currentPath, sizeof(currentPath)) != NULL) {
        this->currentPath = currentPath;
    } else {
        perror("getcwd() error");
    }
}

void WebServer::createVectorOfServers() {
    addConfigInArray<Server>(servers, configLines, "server");
}

void WebServer::fillEachServerWithData() {
    for (size_t i = 0; i < servers.size(); i++) {
        servers[i].addDataInServer();
    }
}

std::string &WebServer::getCurrentPath() {
    return currentPath;
}

std::vector<Server> &WebServer::getServers() {
    return servers;
}

void WebServer::addConfigData() {
    createVectorOfServers();
    fillEachServerWithData();
}

void WebServer::parseConfig() {
    addDataInCurrentPath();
    saveConfigInConfigLine();
    addConfigData();
}

void WebServer::createUniquePair() {
    for (size_t i = 0; i < servers.size(); i++) {
        std::pair<std::string, int> uniquePair = std::make_pair(servers[i].getHost(), servers[i].getPort());
        unique.insert(uniquePair);
    }
}

void WebServer::createEventManager() {
   for (std::set<std::pair<std::string, int> >::iterator it = unique.begin(); it != unique.end(); it++) {
       ServerSocket listenSocket;
       listenSocket.initListenSocket(it->first, it->second);
       eventManager->addServerSocket(listenSocket);
   }
}


void WebServer::start() {
    createUniquePair();
    createEventManager();
    eventManager->copyArray(servers);
    eventManager->waitAndHandleEvents();

//    stop();
}