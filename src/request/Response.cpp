#include "Response.hpp"

//Response::Response(std::string buf, int newsockfd) {
//    buffer = buf;
//    this->newsockfd = newsockfd;
//}
//
//void Response::getUrl() {
//    Request request(buffer);
//    url = request.getUrl();
//    url.erase(0, 1);
//}
//
//void Response::findImage() {
//    if (url.find(".jpg") != std::string::npos || url.find(".png") != std::string::npos ||
//        url.find(".svg") != std::string::npos || url.find(".ico") != std::string::npos) {
//
//        std::ifstream file(url.c_str(), std::ios::binary);
//        if (!file.is_open() || file.fail()){
//            close(newsockfd);
//            return;
//        }
//        std::streampos len = file.seekg(0, std::ios::end).tellg();
//        file.seekg(0, std::ios::beg);
//
//        response = "HTTP/1.1 200 OK\n";
//        if (url.find(".svg") != std::string::npos)
//            response += "Content-Type: image/svg+xml";
//        else {
//            response += "Content-Type: image/";
//            response += url.substr(url.find(".") + 1);
//        }
//        response += "\n";
//        response += "Content-Length: ";
//        response += std::to_string(len);
//        response += "\n\n";
//        std::string line;
//        line.resize(len);
//        file.read(&line[0], len);
//        response += line;
//        response += "\n\n";
//        send(newsockfd, response.c_str(), response.length(), 0);
//        file.close();
//        close(newsockfd);
//        return;
//    }
//}
//
//void Response::createResponse() {
//    std::ifstream file(url.c_str(), std::ios::in | std::ios::binary);
//    std::string response;
//    if (!file.is_open() || file.fail()){
//        response = "HTTP/1.1 404 Not Found\n\n";
//        send(newsockfd, response.c_str(), response.length(), 0);
//        close(newsockfd);
//        return;
//    }
//    response = "HTTP/1.1 200 OK\n\n";
//    std::string line;
//    while (std::getline(file, line)){
//        response += line;
//    }
//    file.close();
//    ssize_t bytesSent = send(newsockfd, response.c_str(), response.length(), 0);
//    if (bytesSent == -1)
//        perror("Error in send");
//
//    close(newsockfd);
//
//}


void Response::handleRequest(std::string buffer, int newsockfd) {
//    getUrl();
//    findImage();
//    createResponse();

    (void)newsockfd;
    //std::cout << buffer << std::endl;
    //response.clear();
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
            return;
        }
        std::streampos len = file.seekg(0, std::ios::end).tellg();
        file.seekg(0, std::ios::beg);

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
        std::cout << "len: " << response.length() << std::endl;
        file.close();
    }
    std::ifstream file(url.c_str(), std::ios::in | std::ios::binary);
    if (!file.is_open() || file.fail()){
        response = "HTTP/1.1 404 Not Found\n\n";
    }
    response = "HTTP/1.1 200 OK\n\n";
    std::string line;
    while (std::getline(file, line, '\0')){
        response += line;
    }
    file.close();
}