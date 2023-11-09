#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

//Этот класс ответственен за создание и управление слушающим сокетом, а также обработку входящих соединений.

class ServerSocket {
public:
    Server();
    ~Server();
    void start();
    void configure(int port, int backlog);
    void stop();

private:
    int listenSocket;
    int port;
    int backlog;
	EventManager eventManager;
    // Другие члены данных для настроек сервера
};


#endif