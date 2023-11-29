#include "Response.hpp"
#include "base64.hpp"

Response::Response() {
    sentLength = 0;
}

void Response::currentPath() {
    char currentPath[PATH_MAX];
    if (getcwd(currentPath, sizeof(currentPath)) != NULL) {
        path = currentPath;
    } else {
        perror("getcwd() error");
    }
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
    }else if (code == 4041) {
        errorPageName = "uniq404.html";
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
    } else if (code == 5001) {
        errorPageName = "uniq500.html";
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
//    std::cout << request.getUrl() << std::endl;
    std::string method = request.getMethod();
    std::string url = request.getUrl();

    this->servers = servers;
    currentPath();
    currentConfig = servers[0];
    chooseConfig(request.getHostName(), currentConfig);
    if (request.request.size() > (size_t)currentConfig.getClientMaxBodySize()) {
        generateErrorsPage(413);
        return;
    }
    std::vector<Location> locations = currentConfig.getLocations();
    chooseLocation(request, currentLocation, locations);
    root = rootParsing(url, locations, currentLocation);
    if (url.find("bin-cgi") == 1) {
        std::string tmp = "/www" + request.getScript();
        request.setScript(tmp);
    }
    if (request.getUrl() == "/")
        request.setUrl(root);
    else if (request.getUrl().find("www") == std::string::npos)
        request.setUrl("/www" + request.getUrl());
    if (url == "/wrong_home_page") {
        generateRedirectResponse(currentLocation.getRedirectPath());
        return;
    }

    //create response for Autoindex
    if (currentLocation.isAutoIndex() && !request.isFile()) {
        generateAutoindexResponse(request);
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
    const char *pythonInterpreter = NULL;
    for (size_t j = 0; j < locations.size(); j++) {
        if (!locations[j].getCgiPass().empty()) {
            pythonInterpreter = locations[j].getCgiPass().c_str();
            break;
        }
    }
    if (!pythonInterpreter) { //это случай когда не нашли интерпретатор, например порт по которому заходит клиент не соответствует конфиг файлу
        generateErrorsPage(500);
        return;
    }
    std::string str = path + request.getScript();
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
    std::string tmpCGIFile = path + "/www/bin-cgi/tmpCGIFile";
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
        std::string formData = request.request.substr(request.request.find("\r\n\r\n") + 4);
        std::istringstream stream(formData);
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
        if (!servers[i].getServerName().empty() && servers[i].getServerName() == hostName && servers[i].getPort() == port) {
            server = servers[i];
            return;
        }
    }
    for (size_t i = 0; i < servers.size(); i++) {
        if (servers[i].getHost() == hostName && servers[i].getPort() == port) {
            server = servers[i];
            return;
        }
    }
}

void Response::chooseLocation(Request request, Location &location, std::vector<Location> locations) {
    for (size_t i = 0; i < locations.size(); i++) {
        if (locations[i].getPathLocation() == request.getUrl()) {
            location = locations[i];
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
        if ((str.find("js") != std::string::npos || str.find("image") != std::string::npos || str.find("bin-cgi") != std::string::npos) && str.find("www") == std::string::npos)
            root = "/www";
        if (locations[j].getPathLocation() == str) {
            currentLocation = locations[j];
            break;
        }
    }
    return root;
}

void Response::generateAutoindexResponse(Request request) {
    DIR *dir;
    struct dirent *ent;
    struct stat filestat;
    std::stringstream html;
    std::string path = request.getUrl();
    if (path.find("www") == std::string::npos)
        path = "/www/" + path;
    html << "<html><body><ul>";
    path = this->path + path;
    dir = opendir(path.c_str());
    if (dir == NULL) {
        generateErrorsPage(404);
        return;
    }
    while ((ent = readdir(dir)) != NULL) {
        std::string filepath = path + ent->d_name;
        stat(filepath.c_str(), &filestat);

        std::string mod_time = ctime(&filestat.st_mtime);
        mod_time = mod_time.substr(0, mod_time.size() - 1);
        if (request.getUrl()[request.getUrl().size() - 1] == '/') {
            html << "<li><a href=\"" << request.getUrl() + ent->d_name << "\">" << ent->d_name << "</a> "
                 << " (size: " << filestat.st_size << ", "
                 << "modified: " << mod_time << ")</li>";
        } else {
            html << "<li><a href=\"" << request.getUrl() + "/" + ent->d_name << "\">" << ent->d_name << "</a> "
                 << " (size: " << filestat.st_size << ", "
                 << "modified: " << mod_time << ")</li>";
        }
    }
    html << "</ul></body></html>";
    closedir(dir);
    response = "HTTP/1.1 200 OK\r\n\r\n" + html.str();
}
