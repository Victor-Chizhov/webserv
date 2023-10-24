#include "../../include/Config.hpp"

Config::Config(std::string pathConfig) {
    this->pathConfig = pathConfig;
}

Config::~Config() {
}

bool Config::checkComments(std::string line) {
    if (line[0] == '#') {
        return true;
    }
    return false;
}

bool Config::findServer(std::string line) {

    if (line.find("server") != std::string::npos) {
        std::cout << "server found" << std::endl;
        return true;
    }
    return false;
}

bool Config::checkNewLine(std::string line) {
    if (line.empty()) {
        return true;
    }
    return false;
}



void Config::parseConfig() {
    std::ifstream inputFile(this->pathConfig);
    if (!inputFile.is_open()) {
        throw std::out_of_range("Error: could not open file");
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        if(checkComments(line)) { continue; }
        else if(findServer(line)) { continue; }
        else if(checkNewLine(line)) { continue; }
        else {
            std::cout << "line: " << line << " ERROR!" << std::endl;
            throw std::out_of_range("Error: invalid config file");
        }
    }
}