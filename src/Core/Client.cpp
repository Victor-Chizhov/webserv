#include "../../include/Client.hpp"

Client::Client(int clientSocket) : clientSocket(clientSocket) {
}

Client::~Client() {
    // Закрытие клиентского сокета при уничтожении объекта
    close(clientSocket);
}

// Метод для чтения данных из клиентского сокета в предоставленный буфер.
ssize_t Client::readData(char* buffer, size_t bufferSize) {
    return read(clientSocket, buffer, bufferSize);
}

// Метод для записи данных из предоставленного буфера в клиентский сокет
ssize_t Client::writeData(const char* data, size_t dataSize) {
    return write(clientSocket, data, dataSize);
}