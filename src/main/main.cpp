/* #include "../../include/Config.hpp" */

/* int main() { */
/*     Config data("/Users/gkhaishb/Desktop/Webserv/config/webserv.conf"); */

/*     try { */
/*         data.parseConfig(); */
/*     } catch (std::exception &e) { */
/*         std::cout << e.what() << std::endl; */
/*     } */

/*     return 0; */
/* } */

#include <iostream>
#include <ratio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8000

int main() {
	// Create socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// Check if socket was created
	if (sockfd < 0) {
		std::cout << "Error creating socket" << std::endl;
		return (1);
	}

	// Bind socket to port
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	// Check if socket was bound
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "Error binding socket" << std::endl;
		return (1);
	}

	// Listen for connections
	if (listen(sockfd, 10) < 0) {
		std::cout << "Error listening socket" << std::endl;
		return (1);
	}

	// Accept connection and create new socket
	int newsockfd = accept(sockfd, NULL, NULL);
	if (newsockfd < 0) {
		std::cout << "Error accepting socket" << std::endl;
		return (1);
	}

	// Read from socket
	char buffer[1024];
	int valread = read(newsockfd, buffer, 1024);

	// Check if read was successful
	if (valread < 0) {
		std::cout << "Error reading socket" << std::endl;
		return (1);
	}
	
	// Print message from client
	std::cout << buffer << std::endl;

	// Send response to client
	std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 12\n\nHello world!";
	send(newsockfd, response.c_str(), response.length(), 0);

	// Close sockets
	close(newsockfd);
	close(sockfd);
	return (0);
}
