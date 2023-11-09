#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <vector>
#include <sys/select.h>
#include <iostream>

//Класс, отвечающий за управление событиями. 

class EventManager {
public:
    EventManager();
    ~EventManager();

    // Метод для добавления клиентского сокета в event-менеджер
    void addClientSocket(int clientSocket);

    // Метод для ожидания событий и их обработки
    void waitAndHandleEvents();

private:
    fd_set readSet;
    std::vector<int> clientSockets;
    int maxSocket;
};



#endif