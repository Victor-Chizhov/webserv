#include "../../include/Config.hpp"


int main(int argc, char **argv) {

    if (argc != 2) {
        std::cout << "Usage: ./webserv <config>" << std::endl;
        return (1);
    }

//    Config config(argv[1]);

    try {
//        config.parseConfig();

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return (1);
    }

	return (0);
}
