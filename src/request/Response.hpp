#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../../include/Libraries.hpp"
#include "Request.hpp"



class Response {
private:
    std::string buffer;
    int newsockfd;
    std::string url;
    std::string response;

    void getUrl();
    void findImage();
    void createResponse();

public:
    Response(std::string buf, int newsockfd);
    void handleRequest();
};


#endif