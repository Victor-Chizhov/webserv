#include "../../include/Config.hpp"
#include "../request/Request.hpp"
#include "../../include/Parser.hpp"
#include "../../include/ServerSocket.hpp"



<<<<<<< HEAD
int main() {
    Config data("config/webserv.conf");

	// // Check if socket was bound
	// if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
	// 	std::cout << "Error binding socket" << std::endl;
	// 	return (1);
	// }

	ServerSocket run;
	run.configure(8065, 120);
	run.start();

	// while (true) {
	// // Listen for connections
	// 	if (listen(sockfd, 10) < 0) {
	// 		std::cout << "Error listening socket" << std::endl;
	// 		return (1);
	// 	}

	// 	// Accept connection and create new socket
	// 	int newsockfd = accept(sockfd, NULL, NULL);
	// 	if (newsockfd < 0) {
	// 		std::cout << "Error accepting socket" << std::endl;
	// 		return (1);
	// 	}
>>>>>>> workwithAlan

    try {
        data.configure(8086, 120);
        data.start();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
