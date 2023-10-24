#include "../../include/Config.hpp"

int main() {
    Config data("/Users/vchizhov/Desktop/webserv/config/webserv.conf");

    try {
        data.parseConfig();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

