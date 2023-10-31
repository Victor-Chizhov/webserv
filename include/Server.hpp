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

    public:
        Server();
        ~Server();

        void setConfig(std::string configLine);

        void printDataConfig() const;
        void addDataInServer();

        void printServerAttributes();
};


#endif
