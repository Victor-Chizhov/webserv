#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../../include/Libraries.hpp"
#include "Response.hpp"

class Response {

public:
    std::string ResponseData;
    int sentLength;

    std::string NumStatus;
    std::string ContentType;
    std::string Status;
    std::string Body;

    void generateDefaultErrorPage(int code);

    Response();

    void getDefaultErrorPage(int code);

    void GenerateContentType(const std::string &path);

    void GenerateErrorStatus(std::string numStatus, std::string contType);
};


#endif