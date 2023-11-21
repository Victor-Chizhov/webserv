#include "Response.hpp"

void Response::handleGet(std::string buffer, int newsockfd) {
//    std::cout << buffer << std::endl;

    Request request(buffer);
//    std::cout << request.getUrl() << std::endl;
    std::string url = request.getUrl();

    if (url == "/")
        url = "/www/index.html";
    if (url.find("www") == std::string::npos)
        url = "/www" + url;

    url.erase(0, 1);
    std::cout << url << std::endl;
    if (url.find(".jpg") != std::string::npos ||
        url.find(".png") != std::string::npos ||
        url.find(".svg") != std::string::npos ||
        url.find(".ico") != std::string::npos) {
//        std::cout << "IMAGE" << std::endl;
        std::ifstream file(url.c_str(), std::ios::binary);
        if (!file.is_open() || file.fail()){
//            std::cout << url << std::endl;
            close(newsockfd);
            return;
        }
        std::streampos len = file.seekg(0, std::ios::end).tellg();
        file.seekg(0, std::ios::beg);

        std::string response;

        response = "HTTP/1.1 200 OK\n";
        if (url.find(".svg") != std::string::npos)
            response += "Content-Type: image/svg+xml";
        else
            response += "Content-Type: image/" + url.substr(url.find(".") + 1);
        response += "\nContent-Length: " + std::to_string(len) + "\n\n";
        std::string line;
        line.resize(len);
        file.read(&line[0], len);
        response += line + "\n\n";
//        std::cout << "len: " << response.length() << std::endl;
        send(newsockfd, response.c_str(), response.length(), 0);
        file.close();
        close(newsockfd);
        return;
    }

    std::ifstream file(url.c_str(), std::ios::in | std::ios::binary);
    std::string response;
    if (!file.is_open() || file.fail()){
        response = "HTTP/1.1 404 Not Found\n\n";
        send(newsockfd, response.c_str(), response.length(), 0);
        close(newsockfd);
        return;
    }
    response = "HTTP/1.1 200 OK\n\n";
    std::string line;
    while (std::getline(file, line)) {
        response += line;
    }
    file.close();
    ssize_t bytesSent = send(newsockfd, response.c_str(), response.length(), 0);
    if (bytesSent == -1) {
        perror("Error in send");
    } else {
//        std::cout << "Sent " << bytesSent << " bytes successfully." << std::endl;
    }

    close(newsockfd);


}

void Response::handlePost(std::string buffer, int newsockfd) {

    std::istringstream request(buffer);
    std::string line;
    std::string boundary;

    while (std::getline(request, line) && line.find("boundary=") == std::string::npos);

    size_t pos = line.find("boundary=");
    if (pos != std::string::npos) {
        boundary = line.substr(pos + 9);
    }

    while (std::getline(request, line) && line != "\r\n");

    // Проверка Content-Disposition на наличие "filename"
    while (std::getline(request, line) && line.find("filename=\"") == std::string::npos);
    size_t filenamePos = line.find("filename=\"");
    if (filenamePos != std::string::npos) {
        std::string filename = line.substr(filenamePos + 10, line.size() - filenamePos - 12);

        std::ofstream outfile(filename.c_str(), std::ios::binary);
        while (std::getline(request, line) && line != "--" + boundary + "--") {
            outfile << line << std::endl;
        }
        outfile.close();

        std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
        send(newsockfd, response.c_str(), response.length(), 0);
    } else {
        std::string response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
        send(newsockfd, response.c_str(), response.length(), 0);
    }

    close(newsockfd);
}


void Response::handleRequest(std::string buffer, int newsockfd) {
//    getUrl();
//    findImage();
//    createResponse();

    if (buffer.find("GET") != std::string::npos) {
        handleGet(buffer, newsockfd);
    } else if (buffer.find("POST") != std::string::npos) {
        handlePost(buffer, newsockfd);
    } else if (buffer.find("DELETE") != std::string::npos) {
        std::cout << buffer << std::endl;
    } else {
        std::cout << "ERROR" << std::endl;
    }


}