#include "../../include/Config.hpp"

int main() {
    Config data("/Users/vchizhov/Desktop/webserv/config/webserv.conf");
    data.parseConfig();

    return 0;
}

