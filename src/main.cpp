#include "../include/Config.hpp"

int main(int argc, char **argv) {
    if (argc != 1) {
        std::cout << "ERROR: many arguments!" << std::endl;
        return 1;
    }

    Config serverConfig("../config/webserv.conf");
    serverConfig.parseConfig();


    return 0;
}

