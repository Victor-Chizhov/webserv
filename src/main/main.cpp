#include "../../include/Config.hpp"
#include "../../include/WebServ.hpp"

int main(int argc, char **argv) {

    try {
        WebServ server;
        if (argc > 2) {
            std::cout << "Too many arguments" << std::endl;
            return 0;
        }
        if (argc == 1) {
            //server.parseConfigFile(DataStorage::root + "/webserv.conf");
        } else {
            //server.parseConfigFile(DataStorage::root + "/" + argv[1]);
			Config config(argv[1]);
			config.parseConfig();
        }
        server.start();
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
