#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../../include/Libraries.hpp"
#include "Request.hpp"
#include "../../include/Server.hpp"

//сделать обработчик для гет запроса с параметрами

class Server;

class Response {
private:


    void getUrl();
    void findImage();
    void createResponse();

    void handleGet(Request &request);
    void handlePost(Request &request);
    void canMakeResponse(Request &request);
    std::vector<Server> servers;
    std::string ipAddress;
    int port;


public:
    Response();
    void handleRequest(Request &request);
    void generateResponse(Request &request, std::vector<Server> const &servers);
    bool isCGI(std::string path);
    void generateCGIResponse(Request &request, std::vector<Server> const &servers);
    void createResponse(Request &request);
    std::string response;
    int sentLength;
    std::string getIpAddress() const;
    void setIpAddress(std::string ipAddress);
    int getPort() const;
    void setPort(int port);
    void generateRedirectResponse(const std::string &locationToRedir);
    void chooseConfig(std::string hostName, Server &server);
    void chooseLocation(std::string hostName, Server &server, std::vector<Location> location);
    std::string rootParsing(const std::string &location, const std::vector<Location> &locations,
                                      Location &currentLocation) const;
};


#endif