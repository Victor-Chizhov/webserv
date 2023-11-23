#include "../../include/EventManager.hpp"

EventManager::EventManager() : maxSocket(0) {
    FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
	FD_ZERO(&read_master);
	FD_ZERO(&write_master);
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
    // clientAddr - структура, в которую будет записан адрес клиента (ip:port), он нужен чтобы потом по частям из него читать или записывать информацию
	socklen_t clientAddrLen = sizeof(clientAddr);
	int clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddr, &clientAddrLen);
	if (clientSocket == -1) {
		perror("Error accepting connection");
		return;
	}
	std::cout << "New connection accepted, socket: " << clientSocket << std::endl;
    fcntl(clientSocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
	/* системный вызов fcntl для установки флага O_NONBLOCK для файлового дескриптора fd. Этот флаг указывает на неблокирующий режим для данного дескриптора.
	В неблокирующем режиме операции ввода-вывода не блокируют выполнение программы, даже если данных на самом деле нет или данные не могут быть записаны. Вместо этого функции чтения и записи возвращают управление сразу, даже если операция не может быть завершена. Это полезно в асинхронных или многозадачных приложениях, где важно избегать блокировки программы в ожидании данных. */
	
    // Добавляем клиентский сокет в множество для использования в select
    FD_SET(clientSocket, &read_master);

    // Обновляем максимальный дескриптор, если необходимо
    if (clientSocket > maxSocket) {
        maxSocket = clientSocket;
    }
	Client *newClient = new Client(clientSocket, clientAddr);
	clientSockets.push_back(newClient);
}

void EventManager::waitAndHandleEvents() {
    while (maxSocket) {
		readSet = read_master;
		writeSet = write_master;
        int activity = select(maxSocket + 1, &readSet, &writeSet, NULL, NULL);
		/* Функция select возвращает количество готовых дескрипторов (сокетов), на которых произошли события, из общего числа дескрипторов в множестве (наборе). Если возвратное значение select равно 0, то это означает, что прошло указанное время ожидания, но ни на одном из дескрипторов не произошло событие. Если значение меньше 0, то произошла ошибка. 
		maxSocket: Это самый большой дескриптор во множестве плюс 1.
		readSet, writeSet, exceptfds(четвертый аргумент): Это три указателя на множества дескрипторов, где readSet используется для отслеживания событий чтения, writeSet - для событий записи, exceptfds - для исключительных событий (ошибок).
		timeout(пятый аргумент): Это указатель на структуру timeval, который определяет максимальное время ожидания. Если timeout установлен в NULL, то select будет ждать бесконечно. */
        if (activity < 0) {
            continue ;
        }
		if (FD_ISSET(serverSockets[0], &readSet)) { // FD_ISSET проверяет готов ли сокет в данном случае для чтения
				CreateAddClientSocket(serverSockets[0]);
		}
		for (std::list<Client *>::iterator it = clientSockets.begin(); it != clientSockets.end(); ++it) {
            Client &current = **it;
			int currentSocket = current.getClientSocket();
			char buffer[1024];
			memset(buffer, 0, 1024);
            if (FD_ISSET(currentSocket, &readSet)) { // FD_ISSET проверяет готов ли сокет в данном случае для чтения
                int bytesRead = recv(currentSocket, buffer, 1024,0);
                if (bytesRead <= 0) {
                    FD_CLR(currentSocket, &read_master);
                    current.request.Parsing(current.request.request);
                    current.response.handleRequest(current.request);
                    current.request.request.clear();
                } else {
                    current.request.request += std::string(buffer, bytesRead);
                }
            }
            if ((current.request.request.find("\r\n\r\n") != std::string::npos )) {
                FD_CLR(currentSocket, &read_master);
                FD_SET(currentSocket, &write_master);
                current.request.Parsing(current.request.request);
                current.response.handleRequest(current.request);
                current.request.request.clear();
            }
            if (FD_ISSET(currentSocket, &writeSet)) {
                int byteToWrite = 1024;
                std::string response = current.response.response;
                int &sentLength = current.response.sentLength;
                int length = current.response.response.size();
                int writingRemainder = length - current.response.sentLength;
                if (byteToWrite > writingRemainder)
                    byteToWrite = writingRemainder;
                int wasSent = 0;
                if (sentLength < length)
                    wasSent = send(currentSocket, response.substr(sentLength).c_str(), byteToWrite, 0);
                if (wasSent == -1 && errno == EPIPE)
                    std::cout << "error in send" << std::endl;
                if(wasSent == -1 || sentLength + wasSent >= length)
                {
                    it = clientSockets.erase(it);
                    --it;
                    close(currentSocket);
                    FD_CLR(currentSocket, &write_master);
                }
                sentLength += wasSent;
            }
		}
	}
}
