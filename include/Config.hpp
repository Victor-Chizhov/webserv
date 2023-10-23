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

class Config {
    protected:
        std::string pathTillConfig;
        

    public:
        Config(std::string pathTillConfig);
        ~Config();
        void parseConfig();
};

#endif