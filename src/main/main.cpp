#include "../../include/Config.hpp"
#include "../request/Request.hpp"
#include "../../include/Parser.hpp"
#include "../../include/ServerSocket.hpp"



int main() {
    ServerSocket data;

    try {
        data.configure(8086, 120);
        data.start();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
