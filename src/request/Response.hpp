#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../../include/Libraries.hpp"
#include "Request.hpp"

//сделать обработчик для гет запроса с параметрами


class Response {
private:


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
    void generateResponse(Request &request);
    bool isCGI(std::string path);
    void generateCGIResponse(Request &request);
    void createResponse(Request &request);
    std::string response;
    int sentLength;
};


#endif