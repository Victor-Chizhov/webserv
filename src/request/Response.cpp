#include "Response.hpp"
Response::Response() {
    sentLength = 0;
}


void Response::handleGet(Request &request) {
    std::string url = request.getUrl();
    url.erase(0, 1);

    if (url.find(".jpg") != std::string::npos ||
        url.find(".png") != std::string::npos ||
        url.find(".svg") != std::string::npos ||
        url.find(".ico") != std::string::npos) {
        std::ifstream file(url.c_str(), std::ios::binary);
        if (!file.is_open() || file.fail()){
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
        file.close();
        return;
    }
    std::ifstream file(url.c_str(), std::ios::in | std::ios::binary);
    if (!file.is_open() || file.fail()){
        response = "HTTP/1.1 404 Not Found\n\n";
        return;
    }
    response = "HTTP/1.1 200 OK\n\n";
    std::string line;
    std::getline(file, line, '\0');
    response += line;
    file.close();
}

void Response::handlePost(Request &request) {
    (void)request;
}


void Response::handleRequest(Request &request) {

    std::cout << request.request << std::endl;

    if(request.getUrl() == "/upload") {

        std::string formData = request.request.substr(request.request.find("\r\n\r\n") + 4);

        std::istringstream stream(formData);

        std::cout << formData << std::endl;

        std::string line;
        std::ofstream destFile;
        destFile.open("upload.txt", std::ios::binary | std::ios::app);

        while (std::getline(stream, line)) {
            destFile << line << std::endl;
        }

        destFile.close();
    }

    if (request.getMethod() == "GET") {
        handleGet(request);
    } else if (request.getMethod() == "POST") {
        handlePost(request);
    } else if (request.getMethod() == "DELETE") {
        std::cout << request.getMethod() << std::endl;
    } else {
        std::cout << "ERROR" << std::endl;
    }
}

void Response::createResponse(Request &request) {
    (void)request;
}
