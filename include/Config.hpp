#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Server.hpp"
#include "Parser.hpp"
#include "Libraries.hpp"

class Config : public Parser {
protected:
        std::string pathConfig;
        std::vector<Server> servers;
        std::vector<std::string> configLines;
        std::set<int> ports;


        bool removeComments(std::string &line);
        void saveConfigInConfigLine();
        void addConfigData();
        void createVectorOfServers();
        void fillEachServerWithData();
        void countPorts();

    public:
        Config(std::string pathConfig);
        void parseConfig();

};


#endif