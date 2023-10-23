#include "../../include/Config.hpp"

Config::Config(std::string pathConfig) {
    this->pathConfig = pathConfig;
    this->configString = NULL;
}

Config::~Config() {
}

Config &Config::operator=(const Config &other) {
    if (this != &other) {
        this->pathConfig = other.pathConfig;
        this->configString = other.configString;
    }
    return *this;
}

void Config::copyDataInServers() {
    std::ifstream inputFile(this->pathConfig);
    if (!inputFile.is_open()) {
        throw std::out_of_range("Error: could not open file");
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }
}

void Config::parseConfig() {
    copyDataInServers();
}