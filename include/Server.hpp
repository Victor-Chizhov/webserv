#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <map>
#include "Location.hpp"

class Server {
    private:
        std::string hostName;
        int port;
        unsigned long clientMaxBodySize;
        std::string serverName;
        std::map<int, std::string> errorPages;
        std::vector<Location> location;

    public:
        Server();
        ~Server();

        void setHostName(std::string hostName);
        void setPort(int port);
        void setClientMaxBodySize(unsigned long clientMaxBodySize);
        void setServerName(std::string serverName);
        void setErrorPages(std::map<int, std::string> errorPages);
        void setLocation(std::vector<Location> location);

        std::string getHostName() const;
        int getPort() const;
        unsigned long getClientMaxBodySize() const;
        std::string getServerName() const;
        std::map<int, std::string> getErrorPages() const;
        std::vector<Location> getLocation() const;

};


#endif
