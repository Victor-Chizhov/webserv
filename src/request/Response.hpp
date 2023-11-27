#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../../include/Libraries.hpp"
#include "Request.hpp"
#include "../../include/Server.hpp"

//сделать обработчик для гет запроса с параметрами

class Server;

class Response {
private:

    std::string ipAddress;
    int port;


    void getUrl();
    void findImage();
    void createResponse();

    void handleGet(Request &request);
    void handlePost(Request &request);
    void canMakeResponse(Request &request);
    void generateErrorsPage(int code);

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
};


#endif