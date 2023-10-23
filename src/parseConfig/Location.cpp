#include "../../include/Location.hpp"

Location::Location() {
    this->root = "";
    this->index = "";
    this->autoIndex = false;
    this->cgiPass = "";
    this->clientMaxBodySize = 0;
    this->fileUpload = false;
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
    }
    return *this;
}

Location::~Location() {
}

void Location::setRoot(std::string root) {
    this->root = root;
}

void Location::setIndex(std::string index) {
    this->index = index;
}

void Location::setAutoIndex(bool autoIndex) {
    this->autoIndex = autoIndex;
}

void Location::setCgiPass(std::string cgiPass) {
    this->cgiPass = cgiPass;
}

void Location::setClientMaxBodySize(unsigned long long clientMaxBodySize) {
    this->clientMaxBodySize = clientMaxBodySize;
}

void Location::setFileUpload(bool fileUpload) {
    this->fileUpload = fileUpload;
}

void Location::setMethods(std::vector<Method> methods) {
    this->methods = methods;
}

std::string Location::getRoot() const {
    return this->root;
}

std::string Location::getIndex() const {
    return this->index;
}

bool Location::getAutoIndex() const {
    return this->autoIndex;
}

std::string Location::getCgiPass() const {
    return this->cgiPass;
}

unsigned long long Location::getClientMaxBodySize() const {
    return this->clientMaxBodySize;
}

bool Location::getFileUpload() const {
    return this->fileUpload;
}

std::vector<Method> Location::getMethods() const {
    return this->methods;
}


