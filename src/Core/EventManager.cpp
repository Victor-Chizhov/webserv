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
				std::cout << "Connection closed or error on socket: " << currentSocket << std::endl;
				close(currentSocket);
				FD_CLR(currentSocket, &readSet);
			} else {
				std::cout << "Received data from socket " << currentSocket << ": " << buffer << std::endl;
				std::string httpRequest(buffer, bytesRead);
                Response response;
				response.handleRequest(httpRequest, currentSocket);
				it = clientSockets.erase(it);
				--it;
			}
		}
	}
}
