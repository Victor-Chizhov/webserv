#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../../include/Libraries.hpp"
#include "Request.hpp"



class Response {
private:
    std::string buffer;
    int newsockfd;
    std::string url;

    void getUrl();
    void findImage();
    void createResponse();

public:
    std::string response;
	int sentLength;
    Response(std::string buf, int newsockfd);
    void handleRequest();
};


#endif