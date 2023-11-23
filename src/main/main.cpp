
#include "../../include/ServerSocket.hpp"
#include "../../include/WebServer.hpp"


int main(int argc, char **argv) {

    (void)argv;

    if (argc != 1) {
        std::cout << "Usage: ./webserv <config>" << std::endl;
        return (1);
    }

    WebServer webserv("/Users/gkhaishb/Desktop/webserv_project/Webserv/config/webserv.conf");

    try {
        webserv.parseConfig();
        webserv.start();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return (1);
    }

	return (0);
}
