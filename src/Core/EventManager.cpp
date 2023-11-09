#include "../../include/EventManager.hpp"

EventManager::EventManager() : maxSocket(0) {
    FD_ZERO(&readSet);
}

EventManager::~EventManager() {
    // Ничего особенного для деструктора, но можно добавить необходимую логику
}

// Метод для добавления клиентского сокета в event-менеджер
void EventManager::addClientSocket(int clientSocket) {
    clientSockets.push_back(clientSocket);
    FD_SET(clientSocket, &readSet);

    if (clientSocket > maxSocket) {
        maxSocket = clientSocket;
    }
}

// Метод для ожидания событий и их обработки
void EventManager::waitAndHandleEvents() {
    while (true) {
        fd_set tempReadSet = readSet;
        int activity = select(maxSocket + 1, &tempReadSet, NULL, NULL, NULL);

        if (activity == -1) {
            perror("Error in select");
            break;
        }

        if (activity > 0) {
            for (int i = 0; i < serverSockets.size(); ++i) {
                int currentSocket = serverSockets[i];
                if (FD_ISSET(currentSocket, &tempReadSet)) {
                    if (currentSocket == listenSocket) {
                        // Если событие на слушающем сокете, это новое подключение
                        int clientSocket = accept(listenSocket, /*...*/);
                        if (clientSocket == -1) {
                            perror("Error accepting connection");
                            // Обработка ошибки при принятии нового соединения
                        } else {
                            std::cout << "New connection accepted, socket: " << clientSocket << std::endl;
                            addClientSocket(clientSocket);
                        }
                    } else {
                        // Обработка других событий, например, чтение данных из клиентского сокета
                        char buffer[1024];
                        ssize_t bytesRead = recv(currentSocket, buffer, sizeof(buffer), 0);
                        if (bytesRead <= 0) {
                            std::cout << "Connection closed or error on socket: " << currentSocket << std::endl;
                            close(currentSocket);
                            FD_CLR(currentSocket, &readSet);
                            serverSockets.erase(serverSockets.begin() + i);
                        } else {
                            std::cout << "Received data from socket " << currentSocket << ": " << buffer << std::endl;
                        }
                    }
                }
            }
        }
    }
}

// Если select() возвращает положительное значение, идем по всем добавленным сокетам, проверяем, какие из них имеют активные события (например, данные для чтения), и обрабатываем их соответственно.

//Если при чтении обнаруживается, что соединение закрыто или произошла ошибка, сокет закрывается, удаляется из fd_set и удаляется из вектора clientSockets.