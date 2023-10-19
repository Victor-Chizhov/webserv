#include "tcpServer.hpp"
#include <ctime>
#include <chrono>

int main() {
    tcpServer server = tcpServer(11111);

    server.runServer();

    return 0;
}