#include "Response.hpp"
#include "base64.hpp"

Response::Response() {
    sentLength = 0;
}

void Response::generateErrorsPage(int code) {
    std::string errorPage;
    std::string errorPagePath = "www/errorPages/";
    std::string errorPageName;
    std::string errorStatus;
    if (code == 400) {
        errorPageName = "400.html";
        errorStatus = "Bad Request";
    } else if (code == 403) {
        errorPageName = "403.html";
        errorStatus = "Forbidden";
    } else if (code == 404) {
        errorPageName = "404.html";
        errorStatus = "Not Found";
    } else if (code == 405) {
        errorPageName = "405.html";
        errorStatus = "Method Not Allowed";
    } else if (code == 413) {
        errorPageName = "413.html";
        errorStatus = "Request Entity Too Large";
    } else if (code == 500) {
        errorPageName = "500.html";
        errorStatus = "Internal Server Error";
    } else if (code == 502) {
        errorPageName = "502.html";
        errorStatus = "Bad Gateway";
    } else if (code == 503) {
        errorPageName = "503.html";
        errorStatus = "Service Unavailable";
    } else
        errorPageName = "404.html";
    response = "HTTP/1.1 " + std::to_string(code) + " " + errorStatus + "\n";
    response += "Content-Type: text/html\n\n";
    std::string line;
    std::ifstream file((errorPagePath + errorPageName).c_str(), std::ios::in | std::ios::binary);
    if (file.is_open()) {
        getline(file, line, '\0');
        file.close();
    }
    response += line;
}

void Response::generateResponse(Request &request, std::vector<Server> const &servers) {
    Server currentConfig;
    Location currentLocation;
    std::string root;

    std::string method = request.getMethod();
    std::string url = request.getUrl();
    this->servers = servers;

    currentConfig = servers[0];
    chooseConfig(request.getHostName(), currentConfig);
    std::vector<Location> locations = currentConfig.getLocations();
    chooseLocation(request.getHostName(), currentConfig, locations);
    root = rootParsing(url, locations, currentLocation);
    if (url.find("bin-cgi") == 1) {
        std::string tmp = "/www" + request.getScript();
        request.setScript(tmp);
    }
    if (request.getUrl() == "/")
        request.setUrl(root);
    else
        request.setUrl(url.insert(url.find('/'), root));
    if (url == "/wrong_home_page") {
        ///generate redirect response with 301 code and Location header where will be currentLocation.getRedirect()
        generateRedirectResponse(currentLocation.getRedirectPath());
        return;
    }

    //generate generateCGIResponse
    if (isCGI(request.getUrl())) {
        generateCGIResponse(request, locations);
        return;
    }

    //generate HTML response
    handleRequest(request);
}

void Response::generateRedirectResponse(const std::string &locationToRedir) {
    std::string str =  "/www";
    response = "HTTP/1.1 301 Moved Permanently\nLocation: " + str + locationToRedir + "\n\n";
}

void Response::generateCGIResponse(Request &request, std::vector<Location> locations) {
//    if (request.getMethod() == "POST" && request.getBody().empty()) {
//        generateErrorsPage(404);
//        return;
//    } это возможно не надо потому что наш cgi работает только с get запросом
    const char *pythonInterpreter = NULL;
    for (size_t j = 0; j < locations.size(); j++) {
        if (!locations[j].getCgiPass().empty()) {
            pythonInterpreter = locations[j].getCgiPass().c_str();
            break;
        }
    }
    if (!pythonInterpreter) { //это случай когда не нашли интерпретатор, например порт по которому заходит клиент не соответствует конфиг файлу
        generateErrorsPage(404);
        return;
    }
    std::string str = "/Users/gkhaishb/Desktop/webserv_project/Webserv" + request.getScript(); //захардкодил путь, потом достать из вебсерва то, что через getcwd Витя получил
    int fdScript = open(str.c_str(), O_RDONLY);
    if (fdScript == -1) { //если путь к скрипту неверный
        perror("Error: open script");
        generateErrorsPage(404);
        return;
    }
    close(fdScript);
    const char *pythonScriptPath = str.c_str();
    std::string pathInfo;
    std::string pathTranslated;
    std::string tmpBodyFile;
    //int hasBody = request.getMethod() == "POST" ? 1 : 0;
    std::map<std::string, std::string> env = request.getArgs();
    char **pythonEnv = new char *[2];
    std::map<std::string, std::string>::iterator it = env.begin();
    std::string tmp = it->first + "=" + it->second; //берем параметры из запроса, пример: Number=3
    if (request.getError() || (str.find("what_day.py") != std::string::npos && it->first != "Number" && !it->first.empty())
    || (str.find("current_time.py") != std::string::npos && tmp != "=")) {
        generateErrorsPage(404);
        return;
    }
    pythonEnv[0] = strdup(tmp.c_str());
    pythonEnv[1] = NULL;
    ///generate args for execve
    char **pythonArgs = new char *[3];
    pythonArgs[0] = strdup(pythonInterpreter);
    pythonArgs[1] = strdup(pythonScriptPath);
    pythonArgs[2] = NULL;
    std::string tmpCGIFile = "/Users/gkhaishb/Desktop/webserv_project/Webserv/www/bin-cgi/tmpCGIFile"; //захардкодил путь к временному файлу, потом переделаю
    int fdCGIFile = open(tmpCGIFile.c_str(), O_RDWR | O_CREAT, 0666);
    if (fdCGIFile == -1) {
        perror("Error open tmpCGIFile");
        exit(1);
    }
    int pid = fork();
    if (!pid) {
        dup2(fdCGIFile, 1);
        if (execve(pythonInterpreter, pythonArgs, pythonEnv) == -1) { //переменная окружения пока не нужна
            perror("Error execve");
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
    if (path.find(".py?") != std::string::npos || path.find(".py/?") != std::string::npos)
        return true;
    return false;
}

void Response::handleGet(Request &request) {
    std::string url = request.getUrl();
    url.erase(0, 1);
    std::cout << "lol azaza " << url << std::endl;
    if (url.find(".jpg") != std::string::npos ||
        url.find(".png") != std::string::npos ||
        url.find(".svg") != std::string::npos ||
        url.find(".ico") != std::string::npos) {
        std::ifstream file(url.c_str(), std::ios::binary);
        if (!file.is_open() || file.fail()) {
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

    //жесткий костыль надо хендлить
    if (url.find("css") != std::string::npos) {
        std::istringstream ss(url);
        std::string segment;
        std::string path;
        while (std::getline(ss, segment, '/'))
            path = segment;

        url = "www/css/" + path;
    }

    std::ifstream file(url.c_str(), std::ios::in | std::ios::binary);
    if (!file.is_open() || file.fail()){
//        response = "HTTP/1.1 404 Not Found\n\n";
        generateErrorsPage(404);
//        std::cout << response << std::endl;
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

    if(request.getUrl() == "/upload") {
    //    std::cout << "----------------------------------------------\n" << request.request << "----------------------------------------------\n" << std::endl;
        // std::cout << "lol" << std::endl;
        std::string formData = request.request.substr(request.request.find("\r\n\r\n") + 4);

        std::istringstream stream(formData);

    //    std::cout << "Body Request: " << formData << std::endl;

        std::string line;
        std::ofstream destFile;
        std::vector<BYTE> vector = base64_decode(formData);
        destFile.open("upload.jpg", std::ios::binary | std::ios::app);
        size_t i = 0;
        while (i < vector.size()) {
            destFile << vector[i];
            i++;
        }

        destFile.close();
    }

    if (request.getMethod() == "GET") {
        handleGet(request);
    } else if (request.getMethod() == "POST") {
        handlePost(request);
    } else if (request.getMethod() == "DELETE") {
        // std::cout << request.getMethod() << std::endl;
    } else {
        // std::cout << "ERROR" << std::endl;
    }
}


void Response::createResponse(Request &request) {
    (void)request;
}

std::string Response::getIpAddress() const {
    return ipAddress;
}

void Response::setIpAddress(std::string ipAddress) {
    this->ipAddress = ipAddress;
}

int Response::getPort() const {
    return port;
}

void Response::setPort(int port) {
    this->port = port;
}

void Response::chooseConfig(std::string hostName, Server &server) {
    for (size_t i = 0; i < servers.size(); i++) {
        if (servers[i].getServerName() == hostName) {
            server = servers[i];
            return;
        }
    }
}

void Response::chooseLocation(std::string hostName, Server &server, std::vector<Location> locations) {
    for (size_t i = 0; i < servers.size(); i++) {
        if (servers[i].getHost() == hostName) {
            server = servers[i];
            locations = servers[i].getLocations();
            return;
        }
    }
}

std::string Response::rootParsing(const std::string &url, const std::vector<Location> &locations,
                                      Location &currentLocation) const {
    std::string root;
    std::string str;
    if (url.find('?') == std::string::npos)
        std::string str = url.substr(0, url.rfind('/'));
    else
    {
        str = url.substr(0, url.rfind('/'));
        str = str.substr(0, str.rfind('/'));
    }
    for (size_t j = 0; j < locations.size(); j++) {
        if (url == "/wrong_home_page")
            str = url;
        if (str.empty())
            str = "/";
        if (url == "/" && locations[j].getPathLocation() == str)
        {
            str = "/www/";
            root = str + locations[j].getIndex();
            break;
        }
        if ((str.find("js") != std::string::npos || str.find("image") != std::string::npos) && str.find("www") == std::string::npos)
            root = "/www";
        if (locations[j].getPathLocation() == str) {
            root = locations[j].getRoot().substr(0, locations[j].getRoot().rfind('/'));
            currentLocation = locations[j];
            break;
        }
    }
    return root;
}