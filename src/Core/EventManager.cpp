#include "../../include/EventManager.hpp"
#include <iostream>
#include <ratio>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <fcntl.h>
#include "../request/Request.hpp"
#include "../../include/Parser.hpp"
#include "../../include/ServerSocket.hpp"

void handleRequest(std::string buffer, int newsockfd)
{
		// Print message from client
		std::cout << buffer << std::endl;

		Request request(buffer);
		std::cout << request.getUrl() << std::endl;
		std::string url = request.getUrl();
		url.erase(0, 1);

		if (url.find(".jpg") != std::string::npos ||
				url.find(".png") != std::string::npos ||
				url.find(".svg") != std::string::npos ||
				url.find(".ico") != std::string::npos) {
			std::cout << "IMAGE" << std::endl;
			std::ifstream file(url.c_str(), std::ios::binary);
			if (!file.is_open() || file.fail()){
				std::cout << url << std::endl;
				close(newsockfd);
				//continue;
				return;
			}
			// get length of file:
			std::streampos len = file.seekg(0, std::ios::end).tellg();
			file.seekg(0, std::ios::beg);

			std::string response;

			response = "HTTP/1.1 200 OK\n";
			if (url.find(".svg") != std::string::npos)
				response += "Content-Type: image/svg+xml";
			else
				response += "Content-Type: image/" + url.substr(url.find(".") + 1);
			response += "\nContent-Length: " + std::to_string(len) + "\n\n";
			std::string line;
			line.resize(len);
			file.read(&line[0], len);
			response += line + "\n\n";
			std::cout << "len: " << response.length() << std::endl;
			send(newsockfd, response.c_str(), response.length(), 0);
			file.close();
			close(newsockfd);
			//continue;
			return;
		}
		std::ifstream file(url.c_str(), std::ios::in | std::ios::binary);
		std::string response;
		if (!file.is_open() || file.fail()){
			response = "HTTP/1.1 404 Not Found\n\n";
			send(newsockfd, response.c_str(), response.length(), 0);
			close(newsockfd);
			//continue;
			return;
		}
		response = "HTTP/1.1 200 OK\n\n";
		std::string line;
		while (std::getline(file, line)){
			response += line;
		}
		file.close();
    ssize_t bytesSent = send(newsockfd, response.c_str(), response.length(), 0);
    if (bytesSent == -1) {
        perror("Error in send");
    } else {
        std::cout << "Sent " << bytesSent << " bytes successfully." << std::endl;
    }

		// Close sockets
		close(newsockfd);
}

EventManager::EventManager() : maxSocket(0) {
    FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
	//FD_ZERO(&read_master);
	//FD_ZERO(&write_master);
}

EventManager::~EventManager() {
    // Ничего особенного для деструктора, но можно добавить необходимую логику
}

// Метод для добавления серверного сокета в event-менеджер
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

    // Обновляем максимальный дескриптор, если необходимо
    if (clientSocket > maxSocket) {
        maxSocket = clientSocket;
    }
	Client *newClient = new Client(clientSocket);
	clientSockets.push_back(newClient);
}

// Метод для ожидания событий и их обработки
void EventManager::waitAndHandleEvents() {
    while (maxSocket) {
		readSet = read_master;
		writeSet = write_master;
        int activity = select(maxSocket + 1, &readSet, &writeSet, NULL, NULL);
		/* Функция select возвращает количество готовых дескрипторов (сокетов), на которых произошли события, из общего числа дескрипторов в множестве (наборе). Если возвратное значение select равно 0, то это означает, что прошло указанное время ожидания, но ни на одном из дескрипторов не произошло событие. Если значение меньше 0, то произошла ошибка. 
		maxSocket: Это самый большой дескриптор во множестве плюс 1.
		readSet, writeSet, exceptfds(четвертый аргумент): Это три указателя на множества дескрипторов, где readSet используется для отслеживания событий чтения, writeSet - для событий записи, exceptfds - для исключительных событий (ошибок).
		timeout(пятый аргумент): Это указатель на структуру timeval, который определяет максимальное время ожидания. Если timeout установлен в NULL, то select будет ждать бесконечно. */

        if (activity <= 0) {
            continue ;
        }

		if (FD_ISSET(serverSockets[0], &readSet)) {
				// Если событие на слушающем сокете, это новое подключение, значит надо создать клиентский сокет и добавить его в list
				CreateAddClientSocket(serverSockets[0]);
		}
		for (std::list<Client *>::iterator it = clientSockets.begin(); it != clientSockets.end(); ++it) {
			//бегаем по всем клиентам и выполняем действия read и write
			int currentSocket = (*it)->getClientSocket();
			// Обработка других событий, например, чтение данных из клиентского сокета
			char buffer[1024];
			memset(buffer, 0, 1024);

			int bytesRead = read(currentSocket, buffer, 1024);
			if (bytesRead <= 0) {
				assert(0);
				std::cout << "Connection closed or error on socket: " << currentSocket << std::endl;
				close(currentSocket);
				FD_CLR(currentSocket, &readSet);
				// clientSockets.erase(it); // To-do: fix iterator invalidatation.
				// --it;
			} else {
				std::cout << "Received data from socket " << currentSocket << ": " << buffer << std::endl;
				std::string httpRequest(buffer, bytesRead);
				handleRequest(httpRequest, currentSocket);
				it = clientSockets.erase(it);
				--it; // Edge cases?
			}
		}
	}
}

// Если select() возвращает положительное значение, идем по всем добавленным сокетам, проверяем, какие из них имеют активные события (например, данные для чтения), и обрабатываем их соответственно.

//Если при чтении обнаруживается, что соединение закрыто или произошла ошибка, сокет закрывается, удаляется из fd_set и удаляется из вектора clientSockets.