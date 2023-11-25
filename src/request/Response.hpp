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

public:
    Response();
    void handleRequest(Request &request);
    std::string response;
    int sentLength;
};


#endif