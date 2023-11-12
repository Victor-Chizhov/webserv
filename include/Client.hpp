#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Libraries.hpp"

class Client {
public:
	Client(int clientSocket);
    ~Client();

    ssize_t readData(char* buffer, size_t bufferSize);
    ssize_t writeData(const char* data, size_t dataSize);
	int getClientSocket() const;
	struct sockaddr_in getStruct() const;


private:
    int clientSocket;
	struct sockaddr_in clientAddr;

};

#endif