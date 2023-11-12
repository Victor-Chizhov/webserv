#include "../../include/WebServ.hpp"

WebServ::WebServ() {
    _eventManager = new EventManager();
}

void WebServ::start() {
    std::cout << "Server started" << std::endl;
    generateListenSockets();
    addListenSocketsToEventManager();
    _eventManager->loop(_listenSockets, _clients);
}

void WebServ::addListenSocketsToEventManager() {
    std::vector<ListenSocket>::iterator it = _listenSockets.begin();
    for (; it != _listenSockets.end(); ++it) {
        _eventManager->registerListeningEvent(it->getSocket());
    }
}

void WebServ::generateListenSockets() {
    std::vector<Server>::iterator it = _servers.begin();

    std::set<std::pair<std::string, int> > uniquePairs;
    for (; it != _servers.end(); ++it)
        uniquePairs.insert(std::make_pair(it->getHost(), it->getPort()));
    std::set<std::pair<std::string, int> >::iterator it2 = uniquePairs.begin();
    for (; it2 != uniquePairs.end(); ++it2) {
        std::vector<Server> servers = getServersByHostAndPort(it2->first, it2->second);
        ListenSocket listenSocket(it2->first, it2->second, servers);
        _listenSockets.push_back(listenSocket);
    }
}

void WebServ::parseConfigFile(const std::string &configFile) {
    // std::ifstream infile(configFile.c_str());
    // if (!infile.is_open())
    //     configError();
    // std::vector<std::string> lines;
    // std::string line;
    // while (std::getline(infile, line)) {
    //     lines.push_back(line);
    // }
    // infile.close();
    // removeComments(lines);
    // for (int i = 0; i < static_cast<int>(lines.size()); ++i) {
    //     if (lines[i] == "server {")
    //         parseServer(lines, _servers, i);
    //     else
    //         configError();
    // }
}

const std::vector<Server> &WebServ::getServers() const {
    return _servers;
}

std::vector<Server> WebServ::getServersByHostAndPort(std::string host, int port) {
    std::vector<Server> serverConfigs;
    std::vector<Server>::iterator it = _servers.begin();
    for (; it != _servers.end(); ++it) {
        if (it->getHost() == host && it->getPort() == port)
            serverConfigs.push_back(*it);
    }
    return serverConfigs;
}

ListenSocket &WebServ::getListenSocketBySocketFd(int socket) {
    std::vector<ListenSocket>::iterator it = _listenSockets.begin();
    for (; it != _listenSockets.end(); ++it) {
        if (it->getSocket() == socket)
            return *it;
    }
    throw std::exception();
}