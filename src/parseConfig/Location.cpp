#include "../../include/Location.hpp"

Location::Location() {
    this->root = "";
    this->index = "";
    this->autoIndex = false;
    this->cgiPass = "";
    this->clientMaxBodySize = 0;
    this->fileUpload = false;
    this->locationConfig = std::vector<std::string>();
    this->methods = std::vector<Method>();
}

Location::Location(const Location &copy) {
    *this = copy;
}

Location &Location::operator=(const Location &copy) {
    if (this != &copy) {
        this->root = copy.root;
        this->index = copy.index;
        this->autoIndex = copy.autoIndex;
        this->cgiPass = copy.cgiPass;
        this->clientMaxBodySize = copy.clientMaxBodySize;
        this->fileUpload = copy.fileUpload;
        this->methods = copy.methods;
        this->locationConfig = copy.locationConfig;
    }
    return *this;
}

Location::~Location() {
}

void Location::setConfig(std::string configLine) {
    this->locationConfig.push_back(configLine);
}

void Location::printDataConfig() const {
    std::cout << "-----------------" << std::endl << "Location Config:" << std::endl << "-----------------" << std::endl;
    for (std::vector<std::string>::const_iterator it = this->locationConfig.begin(); it != this->locationConfig.end(); it++) {
        std::cout << *it << std::endl;
    }
}



