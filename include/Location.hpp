#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include "Method.hpp"

class Location {
    private:
        std::string root;
        std::string index;
        bool autoIndex;
        std::string cgiPass;
        unsigned long long clientMaxBodySize;
        bool fileUpload;
        std::vector<Method> methods;

    public:
        Location();
        Location(const Location &copy);
        Location &operator=(const Location &copy);
        ~Location();

        void setRoot(std::string root);
        void setIndex(std::string index);
        void setAutoIndex(bool autoIndex);
        void setCgiPass(std::string cgiPass);
        void setClientMaxBodySize(unsigned long long clientMaxBodySize);
        void setFileUpload(bool fileUpload);
        void setMethods(std::vector<Method> methods);

        std::string getRoot() const;
        std::string getIndex() const;
        bool getAutoIndex() const;
        std::string getCgiPass() const;
        unsigned long long getClientMaxBodySize() const;
        bool getFileUpload() const;
        std::vector<Method> getMethods() const;

        void print() const;

};

#endif