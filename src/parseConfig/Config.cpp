#include "../../include/Config.hpp"

Config::Config(std::string pathConfig) {
    this->pathConfig = pathConfig;
    this->configLines = std::vector<std::string>();
    this->servers = std::vector<Server>();
}

Config::~Config() {
}

bool Config::removeComments(std::string &line) {
    std::string::size_type pos = line.find('#');
    if (pos != std::string::npos) {
        line.erase(pos);
    }
    return true;
}

void Config::saveConfigInConfigLine() {
    std::ifstream inputFile(this->pathConfig);
    if (!inputFile.is_open()) {
        throw std::out_of_range("Error: could not open file");
    }
    std::string line;
    while(getline(inputFile, line)) {
        removeComments(line);
        if (line.empty()) { continue; }
        configLines.push_back(line);
    }
    inputFile.close();
}

//void Config::copyServConfigInServVector(size_t &index) {
//    Server server;
//    size_t openBrackets = 0;
//    static int id = 0;
//    while (index < configLines.size()) {
//        server.setServerConfig(configLines[index]);
//        if (configLines[index].find("{") != std::string::npos) { openBrackets++; }
//        if (configLines[index].find("}") != std::string::npos) { openBrackets--; }
//        if (openBrackets == 0) { break; }
//        index++;
//    }
//    id++;
//    std::cout << "Server config: " << id << std::endl;
//    server.printServerConfig();
//    servers.push_back(server);
//}
//
//void Config::findServerConfigurations() {
//    for (size_t i = 0; i < configLines.size(); i++) {
//        removeSpaces(configLines[i]);
//        if (configLines[i].find("server{") != std::string::npos) {
//            copyServConfigInServVector(i);
//            continue;
//        }
//    }
//}

void Config::parseConfig() {
    saveConfigInConfigLine();
    addConfigsInArray<Server>(servers, configLines, "server{");
    servers[1].printServerConfig();
}