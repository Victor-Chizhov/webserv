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
    protected:
        std::string pathConfig;
        std::vector<Server *> servers;
        char *configString;

        void copyDataInServers();

        

    public:
        Config(std::string pathConfig);
        ~Config();
        Config &operator=(const Config &other);

        void parseConfig();
};

#endif