#include "Response.hpp"
Response::Response() {
    sentLength = 0;
}


void Response::handleGet(Request &request) {
void Response::generateResponse(Request &request) {
    //generateAutoindexPage

    // generateRedirectResponse //это предложил чатгпт, но пока не работает
    if (request.getMethod() == "GET" && request.getUrl() == "/redirect") {
        response = "HTTP/1.1 301 Moved Permanently\nLocation: http://localhost:8080/\n\n";
        return;
    }

    //generate generateCGIResponse
    if (isCGI(request.getUrl())) {
        generateCGIResponse(request);
        return;
    }

    //generate HTML response
    handleRequest(request);
}

void Response::generateCGIResponse(Request &request) {
    if (request.getMethod() == "POST" && request.getBody().empty()) {
        //generateErrorPage(config, 400);
        return;
    }
    const char *pythonScriptPath = "/Users/gkhaishb/Desktop/webserv_project/Webserv/www/bin-cgi/what_day.py"; //захардкодил путь к скрипту, потом переделаю
    const char *pythonInterpreter = "/usr/bin/python2.7"; //захардкодил путь к интерпретатору, потом переделаю
    std::string pathInfo;
    std::string pathTranslated;
    std::string tmpBodyFile;
    int hasBody = request.getMethod() == "POST" ? 1 : 0;
    std::map<std::string, std::string> env = request.getArgs();
    char **pythonEnv = new char *[2];
    std::map<std::string, std::string>::iterator it = env.begin();
    std::string tmp = it->first + "=" + it->second;
    pythonEnv[0] = strdup(tmp.c_str());
    //pythonEnv[0] = strdup("Number=3"); //цифра захаркодена, потом переделаю (это для второго скрипта какой день недели через n дней)
    pythonEnv[1] = NULL;
    ///generate args for execve
    char **pythonArgs = new char *[3];
    pythonArgs[0] = strdup(pythonInterpreter);
    pythonArgs[1] = strdup(pythonScriptPath);
    pythonArgs[2] = NULL;
    std::string tmpCGIFile = "/Users/gkhaishb/Desktop/webserv_project/Webserv/www/bin-cgi/tmpCGIFile"; //захардкодил путь к временному файлу, потом переделаю
    int fdCGIFile = open(tmpCGIFile.c_str(), O_RDWR | O_CREAT, 0666);
    if (fdCGIFile == -1) {
        perror("Ошибка при открытии файла");
        exit(1);
    }
    int pid = fork();
    if (!pid) {
        dup2(fdCGIFile, 1);
        if (execve(pythonInterpreter, pythonArgs, pythonEnv) == -1) { //переменная окружения пока не нужна
            perror("Ошибка при выполнении execve");
            exit(1);
        }
        close(fdCGIFile);
    }
    std::ifstream file( tmpCGIFile.c_str(), std::ios::binary);
    waitpid(pid, NULL, 0);
    if (file) {
        file.seekg(0, std::ios::end);
        std::streampos length = file.tellg();
        file.seekg(0, std::ios::beg);
        response.resize(length);
        file.read(&response[0], length);
        file.close();
    }
    remove(tmpCGIFile.c_str());
    delete[] pythonArgs;
}

bool Response::isCGI(std::string path) {
    ///check that last 3 symbols is .py
    if (path.size() > 2 && path.substr(path.size() - 3, 3) == ".py")
        return true;
    if (path.find(".py?") != std::string::npos)
        return true;
    return false;
}

void Response::handleRequest(Request &request) {
//    getUrl();
//    findImage();
//    createResponse();

    //std::cout << buffer << std::endl;
    //response.clear();
    std::cout << request.getUrl() << std::endl;
    std::string url = request.getUrl();
    url.erase(0, 1);

    if (url.find(".jpg") != std::string::npos ||
        url.find(".png") != std::string::npos ||
        url.find(".svg") != std::string::npos ||
        url.find(".ico") != std::string::npos) {
        //std::cout << "IMAGE" << std::endl;
        std::ifstream file(url.c_str(), std::ios::binary);
        if (!file.is_open() || file.fail()){
//            std::cout << url << std::endl;
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
        //std::cout << "len: " << response.length() << std::endl;
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

//    std::istringstream request(buffer);
//    std::string line;
//    std::string boundary;
//
//    while (std::getline(request, line) && line.find("boundary=") == std::string::npos);
//
//    size_t pos = line.find("boundary=");
//    if (pos != std::string::npos) {
//        boundary = line.substr(pos + 9);
//    }
//
//    while (std::getline(request, line) && line != "\r\n");
//
//    // Проверка Content-Disposition на наличие "filename"
//    while (std::getline(request, line) && line.find("filename=\"") == std::string::npos);
//    size_t filenamePos = line.find("filename=\"");
//    if (filenamePos != std::string::npos) {
//        std::string filename = line.substr(filenamePos + 10, line.size() - filenamePos - 12);
//
//        std::ofstream outfile(filename.c_str(), std::ios::binary);
//        while (std::getline(request, line) && line != "--" + boundary + "--") {
//            outfile << line << std::endl;
//        }
//        outfile.close();
//
//        std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
//        send(newsockfd, response.c_str(), response.length(), 0);
//    } else {
//        std::string response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
//        send(newsockfd, response.c_str(), response.length(), 0);
//    }
}


void Response::handleRequest(Request &request) {
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
