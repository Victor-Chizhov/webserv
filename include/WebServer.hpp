#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Server.hpp"
#include "Parser.hpp"
#include "Libraries.hpp"
#include "ServerSocket.hpp"


class WebServer : public Parser {
protected:
        std::string pathConfig;
        std::vector<Server> servers;
        std::vector<std::string> configLines;
        std::vector<ServerSocket> serverSockets;
        std::set<unsigned long> ports;


        bool removeComments(std::string &line);
        void saveConfigInConfigLine();
        void addConfigData();
        void createVectorOfServers();
        void fillEachServerWithData();
        void runListenSocket();
        void createStructServerSocket();

        int countPorts();

public:
    WebServer(std::string pathConfig);
    void parseConfig();
    void start();

};


#endif