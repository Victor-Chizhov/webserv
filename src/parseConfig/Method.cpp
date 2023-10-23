#include "../../include/Method.hpp"

Method::Method() {
}

Method::~Method() {
}

int Method::getId() {
    return this->id;
}

void Method::setId(int id) {
    this->id = id;
}

std::string Method::getName() {
    return this->name;
}

void Method::setName(std::string name) {
    this->name = name;
}

