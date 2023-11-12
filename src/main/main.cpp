
#include "../../include/ServerSocket.hpp"
#include "../../include/Config.hpp"


int main(int argc, char **argv) {

    if (argc != 2) {
        std::cout << "Usage: ./webserv <config>" << std::endl;
        return (1);
    }

	ServerSocket run;
//    Config config(argv[1]);

    try {
//        config.parseConfig();
        run.configure(atoi(argv[1]), 120); //???
        run.start();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return (1);
    }

	return (0);
}
