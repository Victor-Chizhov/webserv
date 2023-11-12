#include "../../include/EventManager.hpp"


EventManager::EventManager() : maxSocket(0) {
    FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
	//FD_ZERO(&read_master);
	//FD_ZERO(&write_master);
}

EventManager::~EventManager() {

}

void EventManager::addServerSocket(int ServerSocket) {
    serverSockets.push_back(ServerSocket);
	FD_SET(ServerSocket, &read_master);
	if (ServerSocket > maxSocket) {
        maxSocket = ServerSocket;
    }
}

void EventManager::CreateAddClientSocket(int serverSocket) {
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	int clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddr, &clientAddrLen);
	if (clientSocket == -1) {
		perror("Error accepting connection");
		return;
	}
	std::cout << "New connection accepted, socket: " << clientSocket << std::endl;
	//fcntl(clientSocket, F_SETFL, O_NONBLOCK);
	/* системный вызов fcntl для установки флага O_NONBLOCK для файлового дескриптора fd. Этот флаг указывает на неблокирующий режим для данного дескриптора.
	В неблокирующем режиме операции ввода-вывода не блокируют выполнение программы, даже если данных на самом деле нет или данные не могут быть записаны. Вместо этого функции чтения и записи возвращают управление сразу, даже если операция не может быть завершена. Это полезно в асинхронных или многозадачных приложениях, где важно избегать блокировки программы в ожидании данных. */
	
    // Добавляем клиентский сокет в множество для использования в select
    //FD_SET(clientSocket, &read_master);

    if (clientSocket > maxSocket) {
        maxSocket = clientSocket;
    }
	Client *newClient = new Client(clientSocket);
	clientSockets.push_back(newClient);
}

void EventManager::waitAndHandleEvents() {
    while (maxSocket) {
		readSet = read_master;
		writeSet = write_master;
        int activity = select(maxSocket + 1, &readSet, &writeSet, NULL, NULL);
        if (activity <= 0) {
            continue ;
        }

		if (FD_ISSET(serverSockets[0], &readSet)) {
				CreateAddClientSocket(serverSockets[0]);
		}
		for (std::list<Client *>::iterator it = clientSockets.begin(); it != clientSockets.end(); ++it) {
			int currentSocket = (*it)->getClientSocket();
			char buffer[1024];
			memset(buffer, 0, 1024);

			int bytesRead = read(currentSocket, buffer, 1024);
			if (bytesRead <= 0) {
				assert(0);
				FD_CLR(currentSocket, &readSet);

			} else {
              std::string httpRequest(buffer, bytesRead);
              Response response(httpRequest, currentSocket);
              response.handleRequest();
              it = clientSockets.erase(it);
              --it;
			}
		}
	}
}