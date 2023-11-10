#include "../../include/Config.hpp"
#include "../request/Request.hpp"
#include "../../include/Parser.hpp"

#define PORT 8000

int start() {

    Config data("config/webserv.conf");

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

	while (true) {
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

		Request request(buffer);
		std::cout << request.getUrl() << std::endl;
		std::string url = request.getUrl();
		url.erase(0, 1);

		if (url.find(".jpg") != std::string::npos ||
				url.find(".png") != std::string::npos ||
				url.find(".svg") != std::string::npos ||
				url.find(".ico") != std::string::npos) {
			std::cout << "IMAGE" << std::endl;
			std::ifstream file(url.c_str(), std::ios::binary);
			if (!file.is_open() || file.fail()){
				std::cout << url << std::endl;
				close(newsockfd);
				continue;
			}
			// get length of file:
			std::streampos len = file.seekg(0, std::ios::end).tellg();
			file.seekg(0, std::ios::beg);

			std::string response;

			response = "HTTP/1.1 200 OK\n";
			if (url.find(".svg") != std::string::npos)
				response += "Content-Type: image/svg+xml";
			else {
				response += "Content-Type: image/";
				response += url.substr(url.find(".") + 1);
			}
			response += "\n";
			response += "Content-Length: ";
			response += std::to_string(len);
			response += "\n\n";
			std::string line;
			line.resize(len);
			file.read(&line[0], len);
			response += line;
			response += "\n\n";
			std::cout << "len: " << response.length() << std::endl;
			send(newsockfd, response.c_str(), response.length(), 0);
			file.close();
			close(newsockfd);
			continue;
		}
		std::ifstream file(url.c_str(), std::ios::in | std::ios::binary);
		std::string response;
		if (!file.is_open() || file.fail()){
			response = "HTTP/1.1 404 Not Found\n\n";
			send(newsockfd, response.c_str(), response.length(), 0);
			close(newsockfd);
			continue;
		}
		response = "HTTP/1.1 200 OK\n\n";
		std::string line;
		while (std::getline(file, line)){
			response += line;
		}
		file.close();
		send(newsockfd, response.c_str(), response.length(), 0);

		// Close sockets
		close(newsockfd);
	}
	close(sockfd);
	return (0);
}

int main() {
    Config data("/Users/gkhaishb/Desktop/Webserv/config/webserv.conf");

    try {
        data.parseConfig();
        data.startServers();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
