#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Libraries.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "ListenSocket.hpp"

class Client;
class ListenSocket;

class EventManager {
public:
    EventManager();

    ~EventManager() {};

    void registerListeningEvent(int socket);

    void loop(std::vector<ListenSocket> &serverSockets, std::list<Client> &clientSockets);

    int getMaxEvents() const;

private:
    static const int maxEvents = 63000;
    int _kq;
    typedef struct kevent kEvent;
    std::list<kEvent> _eventsList;
    kEvent _eventsArr[maxEvents];

    int getEventsNumber();

    int getListenSocketFd(std::vector<ListenSocket> &Sockets, int currentEventSocket) const;

    int getClientFd(std::list<Client> &Sockets, int currentEventSocket) const;

    void validateEOF(Client &clientSocket, const EventManager::kEvent &event) const;

    void addClientEvent(const Client &clientSocket) const;

    void RemoveClientEvent(const Client &clientSocket) const;

    void readRequest(Client &clientSocket, const kEvent &event) const;

    void writeResponse(Client &clientSocket, std::list<Client> &clientSockets) const;

    Client &getClientBySocketFd(std::list<Client> &clientSockets, int fd);

    ListenSocket &getListenSocketBySocketFd(std::vector<ListenSocket> &serverSockets, int fd);

    void createResponse(Client &clientSocket) const;
};

#endif