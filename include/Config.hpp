#ifndef CONFIG_HPP
#define CONFIG_HPP


#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <map>
#include "Server.hpp"
#include <fstream>

class Config {
    private:
        std::string pathConfig;
        std::vector<Server> servers;
        std::vector<std::string> configLines;

        bool removeComments(std::string &line);
        void findServerConfigurations();
        void saveConfigInConfigLine();

    public:
        Config(std::string pathConfig);
        ~Config();
        void parseConfig();
};


#endif