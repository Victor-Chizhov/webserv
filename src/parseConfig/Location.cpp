#include "../../include/Location.hpp"

Location::Location() {
    this->root = "";
    this->index = "";
    this->autoIndex = false;
    this->cgiPass = "";
    this->clientMaxBodySize = 0;
    this->fileUpload = false;
    this->locationConfig = std::vector<std::string>();
    this->methods = std::vector<std::string>();
    this->pathLocation = "";
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
        this->pathLocation = copy.pathLocation;
    }
    return *this;
}

void Location::setConfig(std::string &configLine) {
    this->locationConfig.push_back(configLine);
}

void Location::printDataConfig() const {
    std::cout << "-----------------" << std::endl << "Location WebServer:" << std::endl << "-----------------" << std::endl;
    for (std::vector<std::string>::const_iterator it = this->locationConfig.begin(); it != this->locationConfig.end(); it++) {
        std::cout << *it << std::endl;
    }
}

void Location::printLocationData() {
    std::cout << "-----------------" << std::endl << "Location WebServer:" << std::endl << "-----------------" << std::endl;
    std::cout << "pathLocation: " << pathLocation << std::endl;
    std::cout << "root: " << root << std::endl;
    std::cout << "index: " << index << std::endl;
    std::cout << "autoIndex: " << autoIndex << std::endl;
    std::cout << "cgiPass: " << cgiPass << std::endl;
    std::cout << "clientMaxBodySize: " << clientMaxBodySize << std::endl;
    std::cout << "fileUpload: " << fileUpload << std::endl;
    for (std::vector<std::string>::iterator it = methods.begin(); it != methods.end(); ++it) {
        std::cout <<  "Methods: " << *it << std::endl;
    }
}

void Location::updateDataInLocation() {
    for (size_t i = 0; i < locationConfig.size(); i++) {
        cutDataStr(locationConfig[i], "location", pathLocation);
        cutDataStr(locationConfig[i], "root", root);
        cutDataBool(locationConfig[i], "autoindex", autoIndex);
        cutDataStr(locationConfig[i], "index", index);
        cutDataStr(locationConfig[i], "cgi_pass", cgiPass);
        cutDataNum(locationConfig[i], "client_max_body_size", clientMaxBodySize);
        cutDataBool(locationConfig[i], "file_upload", fileUpload);
        cutDataArray(locationConfig[i], "methods", methods);
    }
}



