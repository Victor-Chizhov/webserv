#include "../../include/EventManager.hpp"


EventManager::EventManager() : maxSocket(0) {
    FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
}

EventManager::~EventManager() {

}

void EventManager::addServerSocket(int ServerSocket) {
    serverSockets.push_back(ServerSocket);
	FD_SET(ServerSocket, &readSet);
	maxSocket = ServerSocket;
}

void EventManager::CreateAddClientSocket(int serverSocket) {
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	int clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddr, &clientAddrLen);
	if (clientSocket == -1) {
		perror("Error accepting connection");
		return;
	}

    if (clientSocket > maxSocket) {
        maxSocket = clientSocket;
    }
	Client *newClient = new Client(clientSocket);
	clientSockets.push_back(newClient);
}

void EventManager::waitAndHandleEvents() {
    while (maxSocket) {
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