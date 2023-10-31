#include "../../include/Config.hpp"

Config::Config(std::string pathConfig) {
    this->pathConfig = pathConfig;
    this->configLines = std::vector<std::string>();
    this->servers = std::vector<Server>();
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

void Config::addConfigData() {
    addConfigInArray<Server>(servers, configLines, "server");
    for (size_t i = 0; i < servers.size(); i++) {
        servers[i].addDataInServer();
    }
}

void Config::parseConfig() {
    saveConfigInConfigLine();
    addConfigData();
}