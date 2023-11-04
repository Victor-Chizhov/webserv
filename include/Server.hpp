#ifndef SERVER_HPP
#define SERVER_HPP


#include "Parser.hpp"
#include "Location.hpp"

class Server : public Parser {
    private:
        std::vector<std::string> serverConfig;
        std::string ipAddress;
        unsigned long port;
        unsigned long clientMaxBodySize;
        std::string serverName;
        std::map<int, std::string> errorPages;
        std::vector<Location> locations;

        void createVectorOfLocations();
        void fillEachLocationWithData();
        void updateDataInServer();

    public:
        Server();

        void setConfig(std::string &configLine);
        void addDataInServer();

        void printServerData();
        void printDataConfig() const;

};


#endif
