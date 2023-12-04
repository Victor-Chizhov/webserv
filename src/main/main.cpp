
#include "../../include/ServerSocket.hpp"
#include "../../include/WebServer.hpp"


int main(int argc, char **argv) {

    (void)argv;
    signal(SIGPIPE, SIG_IGN);
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
