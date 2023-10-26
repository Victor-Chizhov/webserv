#ifndef SERVER_HPP
#define SERVER_HPP


#include "Parser.hpp"

class Server : public Parser {
    private:
        std::vector<std::string> serverConfig;
        std::string ipAddress;
        unsigned long port;
        unsigned long clientMaxBodySize;
        std::string serverName;
        std::map<int, std::string> errorPages;
        std::vector<Location> location;

    public:
        Server();
        ~Server();

        void setPort(int port);
        void setClientMaxBodySize(unsigned long clientMaxBodySize);
        void setServerName(std::string serverName);
        void setErrorPages(std::map<int, std::string> errorPages);
        void setLocation(std::vector<Location> location);
        void setServerConfig(std::string serverConfig);
        void setIpAddress(std::string ipAddress);


        int getPort() const;
        unsigned long getClientMaxBodySize() const;
        std::string getServerName() const;
        std::map<int, std::string> getErrorPages() const;
        std::vector<Location> getLocation() const;
        std::string getIpAddress() const;

        void printServerConfig() const;
        void printServerAttributes();
        void addAttributesInServer();





};


#endif
