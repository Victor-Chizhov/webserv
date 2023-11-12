#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Libraries.hpp"
#include "Server.hpp"
#include "../src/request/Request.hpp"
#include "../src/request/Response.hpp"
#include "ListenSocket.hpp"

class Server;

class Client : public ListenSocket {
private:
    typedef struct kevent kEvent;
    kEvent _clientInterest;
    std::string _read;
    size_t _much_written;
    bool _isReadyToMakeResponse;
	
public:
    int ResponseSize;
    Request Request;
    Response Response;

    Client(int socket, int kq, const std::vector<Server> &configs);

    bool generateAutoindexPage(const std::string &rootPath, const std::string &location);

    const std::string &getRead() const {
        return _read;
    }

    size_t getMuchWritten() const {
        return _much_written;
    }

    bool isValidRequest() const;

    void generateCGIResponse(const std::string &path, const Location &location, const std::string &pathToUpload,
                             const Server &config);

    void generateResponse();

    Client(const Client &socket);

    Client &operator=(const Client &socket);

    ~Client() {};

    ///generate == operator
    bool operator==(const Client &socket) const;

    void getFoolPath(std::string &pathToUpdate) const;

    void getDataByFullPath(const std::string &path, const Server &config, const Location &location,
                           const std::string
                           &pathAfterCGIScript);

    void getErrorPageData(const std::string &errorRoot);

    void generateErrorPage(const Server&config, int errorNumber);

    bool isValidMethod(const std::string &method, const Location &location);

    bool isCGI(std::string path);

    bool CanMakeResponse();

    void parseRequestPath(std::string &fileToOpen, std::string &placeToUpload, std::string &location);

    std::string rootParsing(const std::string &location, const std::vector<Location> &locations,
                            Location &currentLocation) const;

    void chooseLocation(const std::string &host, Server &currentConfig, std::vector<Location> &locations);

    bool isValidRequest(const Server &currentConfig, const Location &currentLocation, const std::string &method,
                        const std::string &root, bool isAutoindex);

    void generateAutoindexResponse(Server &config);

    void deleteFile(const std::string &fileToOpen, std::string &root);

    void generateRedirectResponse(const std::string &locationToRedir);

    void chooseConfig(const std::string &host, Server &config);
};

#endif