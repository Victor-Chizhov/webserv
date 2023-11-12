#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../../include/Libraries.hpp"
#include "Request.hpp"



class Response {
private:


    void getUrl();
    void findImage();
    void createResponse();

    void handleGet(std::string buffer, int newsockfd);

public:

    void handleRequest(std::string buffer, int newsockfd);
};


#endif