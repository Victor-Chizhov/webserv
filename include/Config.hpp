#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Server.hpp"
#include "Parser.hpp"


class Config : public Parser {
    private:
        std::string pathConfig;
        std::vector<Server> servers;
        std::vector<std::string> configLines;

        bool removeComments(std::string &line);
        void saveConfigInConfigLine();
        void addConfigData();

    public:
        Config(std::string pathConfig);
        void parseConfig();

};


#endif