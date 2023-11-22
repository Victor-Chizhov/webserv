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
    void handleRequest(std::string buffer, int newsockfd);
    std::string response;
};


#endif