#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include "Method.hpp"

class Location {
    protected:
        std::string root;
        std::string index;
        bool autoIndex;
        std::string cgiPass;
        unsigned long long clientMaxBodySize;
        bool fileUpload;
        std::vector<Method> methods;



    public:

};

#endif