#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <map>

class Server {
    protected:
        std::string hostName;
        int port;
        unsigned long clientMaxBodySize;
        std::string serverName;
        std::map<int, std::string> errorPages;




    public:
        Server();
        ~Server();
};


#endif
