#include "../../include/Config.hpp"

int main() {
    Config data("/Users/gkhaishb/Desktop/Webserv/config/webserv.conf");

    try {
        data.parseConfig();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

