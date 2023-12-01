
#include "../../include/ServerSocket.hpp"
#include "../../include/WebServer.hpp"


int main(int argc, char **argv) {

    (void)argv;
    signal(SIGPIPE, SIG_IGN); //что-бы сервер не падал, когда клиент закрывает сокет, а мы пытаемся в него записать что-то
    if (argc != 1) {
        std::cout << "Usage: ./webserv <config>" << std::endl;
        return (1);
    }

    WebServer webserv("config/webserv.conf");

    try {
        webserv.parseConfig();
        webserv.start();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return (1);
    }

	return (0);
}
