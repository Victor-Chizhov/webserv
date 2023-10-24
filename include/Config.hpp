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

        bool checkComments(std::string line);
        bool findServer(std::string line);
        bool checkNewLine(std::string line);


    public:
        Config(std::string pathConfig);
        ~Config();

        void parseConfig();
};


// remove space for string
template<class ForwardIt, class T>
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
{
    first = std::find(first, last, value);
    if (first != last)
        for (ForwardIt i = first; ++i != last;)
            if (!(*i == value))
                *first++ = std::move(*i);
    return first;
}

#endif