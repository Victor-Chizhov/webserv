#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../../include/Libraries.hpp"
#include "Request.hpp"



class Response {
private:


    void getUrl();
    void findImage();
    void createResponse();

public:
//    Response(std::string buf, int newsockfd);
    Response();
    void handleRequest(Request &request);
    void generateResponse(Request &request);
    bool isCGI(std::string path);
    void generateCGIResponse(Request &request);
    std::string response;
    int sentLength;
};


#endif