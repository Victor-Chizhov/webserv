#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../../include/Libraries.hpp"

class Request {
public:
    std::string RequestData;

    bool hasCGI();

    void parse_request(const std::string &request);

    const std::string &getMethod() const;

    const std::string &getPath() const;

    bool isVersion() const;

    const std::map<std::string, std::string> &getHeaders() const;

    const std::string &getBody() const;

    const std::map<std::string, std::string> &getArgs() const;

    int Error;
    bool hasError;

    Request();

private:
    std::string method;
    std::string path;
    std::map<std::string, std::string> args;
    bool version;
    std::map<std::string, std::string> headers;
    std::string body;
};


#endif //WEBSERV_REQUEST_HPP